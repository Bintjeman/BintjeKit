/*!
 * @file input_binding_manager.cpp
 * path include/bintjekit/event_manager
 * partie du projet: Binjekit
 * @author bintjeman
 * @date 18.07.25
 */
#include "bintjekit/event_manager/input_binding_manager.hpp"
namespace bnjkit::event {
}
bool KeyBinding::operator==(const KeyBinding& other) const {
    return key == other.key &&
           ctrl == other.ctrl &&
           shift == other.shift &&
           alt == other.alt;
}
std::size_t KeyBindingHash::operator()(const KeyBinding& kb) const {
    std::size_t h = std::hash<int>{}(static_cast<int>(kb.key));
    h ^= std::hash<bool>{}(kb.ctrl) << 1;
    h ^= std::hash<bool>{}(kb.shift) << 2;
    h ^= std::hash<bool>{}(kb.alt) << 3;
    return h;
}
void bnjkit::event::InputBindingManager::
bind_key_to_action(const KeyBinding& binding, const std::string& action_name) {
    m_keyBindings[binding] = action_name;
}
