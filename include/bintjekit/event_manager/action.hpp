/*!
 * @file action.hpp
 * path include/bintjekit/event_manager
 * partie du projet: Binjekit
 * @author bintjeman
 * @date 18.07.25
 */
#ifndef BINTJEKIT_EVENT_ACTION_HPP
#define BINTJEKIT_EVENT_ACTION_HPP
#pragma once
#include <functional>
#include <string>
namespace bnjkit::event {
    class Action {
    public:
        using Callback = std::function<void()>;
        Action(const std::string& name, const Callback& callback);
        void execute() const;
        [[nodiscard]] const std::string& get_name() const;

    private:
        std::string m_name;
        Callback m_callback;
    };
};

}
#endif
