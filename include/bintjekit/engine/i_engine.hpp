/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.hpp
 */
#ifndef BNJKIT_ENGINE_I_ENGINE_HPP
#define BNJKIT_ENGINE_I_ENGINE_HPP
#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"

namespace bnjkit {

    namespace engine {
        struct PlayGround;

        class IEngine : public core::IModule, public event::IEventListener {
        public:
            enum class State {
                READY,
                FINISH,
                EMPTY,
            };

            IEngine();
            ~IEngine() override;
            void initialise() override;
            void configure() override;
            virtual void update();
            [[nodiscard]] State state() const;

        protected:
            State m_state{State::EMPTY};
            std::shared_ptr<spdlog::logger> m_logger;

        public:
            static std::string state_to_string(State state);
            void on_sfml_event(const sf::Event& event) override;
            [[nodiscard]] std::string name() const override;
        };
    } // engine
} // bnjkit

#endif // BNJKIT_ENGINE_I_ENGINE_HPP
