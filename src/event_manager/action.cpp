/*!
 * @file action.cpp
 * path include/bintjekit/event_manager
 * partie du projet: Binjekit
 * @author bintjeman
 * @date 18.07.25
 */
#include "bintjekit/event_manager/action.hpp"

namespace bnjkit::event {
    Action::Action(const std::string& name, const Callback& callback): m_name(name), m_callback(callback) {
    }

    void Action::execute() const {
        if (m_callback) {
            m_callback();
        }
    }

    const std::string& Action::get_name() const { return m_name; }
}
