/*!
 * @author bintjeman
 * @date 19.06.25
 * @name node.inl
 */
#ifndef BNJKIT_CONFIGURATION_NODE_INL
#define BNJKIT_CONFIGURATION_NODE_INL
#pragma once
namespace bnjkit::conf {
    template<typename T>
    T Node::get(const nlohmann::json::json_pointer& key, const T& default_value) const {
        const nlohmann::json_pointer<std::string> ptr = m_branch / key;
        if (!m_json->contains(ptr)) {
            return default_value;
        }
        return m_json->at(ptr).get<T>();
    }
    template<typename T>
    T Node::get(const nlohmann::json::json_pointer& key) const {
        const auto ptr = m_branch / key;
        if (!m_json->contains(ptr)) {
            return T{};
        }
        return m_json->at(ptr).get<T>();
    }
    template<typename T>
    T Node::get_or_set(const nlohmann::json::json_pointer& key, const T& default_value) {
        const nlohmann::json_pointer<std::string> ptr = m_branch / key;
        if (!m_json->contains(ptr)) {
            (* m_json)[m_branch / key] = default_value;
            return default_value;
        }
        return m_json->at(ptr).get<T>();
    }
    template<typename T>
    void Node::set(const nlohmann::json::json_pointer& key, const T& value) {
        (* m_json)[m_branch / key] = value;
    }
    template<typename T>
    T Node::get(const std::string& key, const T& default_value) const {
        return get<T>(nlohmann::json::json_pointer(key), default_value);
    }
    template<typename T>
    T Node::get(const std::string& key) const {
        return get<T>(nlohmann::json::json_pointer(key));
    }
    template<typename T>
    T Node::get_or_set(const std::string& key, const T& default_value) {
        return get_or_set<T>(nlohmann::json::json_pointer(key), default_value);
    }
    template<typename T>
    void Node::set(const std::string& key, const T& value) {
        set<T>(nlohmann::json::json_pointer(key), value);
    }
}
#endif // BNJKIT_CONFIGURATION_NODE_INL
