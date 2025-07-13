/*!
 * @author bintjeman
 * @date 13.07.25
 * @name event_bus.hpp
 */

#ifndef BINTJEKIT_ENGINE_EVENT_MANAGER_HPP
#define BINTJEKIT_ENGINE_EVENT_MANAGER_HPP
#pragma once
#include <functional>
#include <memory>

namespace bnjkit::engine {
    template<typename Event>
    class EventDispatcher {
    public:
        void emit(const Event& event) {
            for (auto& listener: m_listeners) {
                listener(event);
            }
        }

        void subscribe(std::function<void(const Event&)> callback) {
            m_listeners.push_back(callback);
        }

    private:
        std::vector<std::function<void(const Event&)> > m_listeners;
    };

    class EventBus {
    public:
        template<typename Event>
        void emit(const Event& event) {
            get_dispatcher<Event>().emit(event);
        }

        template<typename Event>
        void subscribe(std::function<void(const Event&)> callback) {
            get_dispatcher<Event>().subscribe(callback);
        }

    private:
        template<typename Event>
        EventDispatcher<Event>& get_dispatcher() {
            auto& dispatcher = m_dispatchers[typeid(Event).hash_code()];
            if (!dispatcher) {
                dispatcher = std::make_unique<EventDispatcher<Event> >();
            }
            return * static_cast<EventDispatcher<Event>*>(dispatcher.get());
        }

        std::unordered_map<size_t, std::unique_ptr<void> > m_dispatchers;
    };
}

#endif //BINTJEKIT_ENGINE_EVENT_MANAGER_HPP
