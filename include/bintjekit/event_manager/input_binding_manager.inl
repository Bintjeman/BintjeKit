/*!
 * @author bintjeman
 * @date 18.07.25
 * @name input_binding_manager.inl
 */
#ifndef BINTJEKIT_INPUT_BINDING_MANAGER_INL
#define BINTJEKIT_INPUT_BINDING_MANAGER_INL
#pragma once
namespace bnjkit::event {
    template<typename... Args>
    void InputBindingManager::register_action(const std::string& action_name,
                                              const typename Action<Args...>::Callback& callback) {
        m_actions[action_name] = std::make_shared<Action<Args...> >(action_name, callback);
    }
    template<typename... Args>
    void InputBindingManager::process_key_press(const KeyBinding& binding, Args&&... args) {
        auto it = m_keyBindings.find(binding);
        if (it != m_keyBindings.end()) {
            auto actionIt = m_actions.find(it->second);
            if (actionIt != m_actions.end()) {
                if (auto action = std::dynamic_pointer_cast<Action<Args...> >(actionIt->second)) {
                    action->execute(std::forward<Args>(args)...);
                }
            }
        }
    }
}
#endif // BINTJEKIT_INPUT_BINDING_MANAGER_INL
