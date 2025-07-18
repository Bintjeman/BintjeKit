/*!
 * @file input_binding_manager.cpp
 * path include/bintjekit/event_manager
 * partie du projet: Binjekit
 * @author bintjeman
 * @date 18.07.25
 */
#include "bintjekit/event_manager/input_binding_manager.hpp"
namespace bnjkit::event {
    void InputBindingManager::register_action(const std::string& action_name, const Action::Callback& callback) {
        m_actions[action_name] = std::make_shared<Action>(action_name, callback);

    }
    void InputBindingManager::bindKeyToAction(sf::Keyboard::Key key, const std::string& action_name) {
        m_keyBindings[key] = action_name;
    }

    void InputBindingManager::process_key_press(sf::Keyboard::Key key) {
        auto it = m_keyBindings.find(key);
        if (it != m_keyBindings.end()) {
            auto actionIt = m_actions.find(it->second);
            if (actionIt != m_actions.end()) {
                actionIt->second->execute();
            }
        }
    }

    void InputBindingManager::save_bindings(const std::string& filename) {
    }

    void InputBindingManager::loadBindings(const std::string& filename) {
    }
}
