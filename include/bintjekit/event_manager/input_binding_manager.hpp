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

struct KeyBinding {
    sf::Keyboard::Key key;
    bool shift{false};
    bool ctrl{false};
    bool alt{false};

    // Pour utiliser la structure comme clé dans unordered_map
    bool operator==(const KeyBinding& other) const;
};

// Fonction de hachage pour KeyBinding
struct KeyBindingHash {
    std::size_t operator()(const KeyBinding& kb) const;
};

namespace bnjkit::event {
    class InputBindingManager {
    public:
        template<typename... Args>
        void register_action(const std::string& action_name, const typename Action<Args...>::Callback& callback);
        template<typename... Args>
        void process_key_press(const KeyBinding& binding, Args&&... args);
        void bind_key_to_action(const KeyBinding& binding, const std::string& action_name);

    private:
        std::unordered_map<std::string, std::shared_ptr<void> > m_actions;
        std::unordered_map<KeyBinding, std::string, KeyBindingHash> m_keyBindings;
    };
    // /////////////////////////////////////////////////////////////////////////
}

#include "input_binding_manager.inl"
#endif
