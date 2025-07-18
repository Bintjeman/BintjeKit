/*!
 * @file input_binding_manager.hpp
 * path include/bintjekit/event_manager
 * partie du projet: Binjekit
 * @author bintjeman
 * @date 18.07.25
 */
#ifndef BNJKIT_EVENT_INPUT_BINDING_MANAGER_HPP
#define BNJKIT_EVENT_INPUT_BINDING_MANAGER_HPP
#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "action.hpp"

namespace sf::Keyboard {
    enum class Key;
}

namespace bnjkit::event {
    class InputBindingManager {
    public:
        void register_action(const std::string& action_name, const Action::Callback& callback);
        void bind_key_to_action(sf::Keyboard::Key key, const std::string& action_name);
        void process_key_press(sf::Keyboard::Key key);
        // Méthode pour sauvegarder/charger les bindings
        void save_bindings(const std::string& filename);
        void load_bindings(const std::string& filename);

    private:
        std::unordered_map<std::string, std::shared_ptr<Action> > m_actions;
        std::unordered_map<sf::Keyboard::Key, std::string> m_keyBindings;
    };
    ;
}
#endif
