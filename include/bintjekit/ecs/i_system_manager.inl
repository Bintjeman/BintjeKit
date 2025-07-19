/*!
 * @author bintjeman
 * @date 16.07.25
 * @name i_system_manager.inl
 */

#ifndef BINTJEKIT_ECS_I_SYSTEM_MANAGER_INL
#define BINTJEKIT_ECS_I_SYSTEM_MANAGER_INL
#pragma once
#include "bintjekit/logger.hpp"

namespace bnjkit::ecs {
    template<typename SystemType>
    SystemEntry<
        SystemType>::SystemEntry(std::unique_ptr<SystemType> sys, std::string n, bool e): system(std::move(sys)),
        name(std::move(n)), enabled(e) {}
    template<typename SystemType, typename PriorityType>
    SystemManager<SystemType, PriorityType>::SystemManager() {
        m_logger = logger::Logger::get_logger(literals::logger::ECS);
        m_logger->info("SystemManager <{}, {}> created", typeid(SystemType).name(), typeid(PriorityType).name());
    }
    template<typename SystemType, typename PriorityType>
    SystemManager<SystemType, PriorityType>::~SystemManager() {
        m_logger->info("SystemManager <{}, {}> destroyed", typeid(SystemType).name(), typeid(PriorityType).name());
    }
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::initialise() {}
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::configure() {}
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::on_quit() {}
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::
    add_system(std::unique_ptr<SystemType> system, PriorityType priority) {
        m_logger->trace("SystemManager {}: Adding system", typeid(SystemType).name());
        const std::string system_name = system->name();
        m_logger->trace("Adding system: {}", system_name);
        if (m_systems.find(priority) == m_systems.end()) {
            m_systems[priority] = std::vector<SystemEntry<SystemType> >();
        }
        size_t index = m_systems[priority].size();
        m_systems[priority].push_back({
            std::move(system),
            system_name,
            true
        });
        m_system_registry[system_name] = {priority, index};
    }
    template<typename SystemType, typename PriorityType>
    bool SystemManager<SystemType, PriorityType>::remove_system(const std::string& name) {
        auto it = m_system_registry.find(name);
        if (it == m_system_registry.end()) {
            m_logger->warn("Attempt to remove non-existent system: {}", name);
            return false;
        }
        auto [layer, index] = it->second;
        auto& systems = m_systems[layer];
        if (index >= systems.size()) {
            m_logger->error("Invalid system index: {}", name);
            return false;
        }
        // Suppression du système
        systems.erase(systems.begin() + static_cast<std::ptrdiff_t>(index));
        m_system_registry.erase(it);
        // Mise à jour des indices dans le registre
        for (auto& [name_, location]: m_system_registry) {
            if (location.first == layer && location.second > index) {
                -- location.second;
            }
        }
        m_logger->info("System {} removed : {}", typeid(SystemType).name(), name);
        return true;
    }
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::clear() {
        m_systems.clear();
        m_system_registry.clear();
        m_logger->info("SystemManager {}: All systems cleared", typeid(SystemType).name());
    }
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::toggle_system(const std::string& name, bool enable) {
        auto index = m_system_registry[name];
        m_systems[index.first][index.second].enabled = enable;
    }
    template<typename SystemType, typename PriorityType>
    SystemType& SystemManager<SystemType, PriorityType>::system(const std::string& name) {
        auto index = m_system_registry[name];
        return *m_systems[index.first][index.second].system;
    }
    template<typename SystemType, typename PriorityType>
    const SystemType& SystemManager<SystemType, PriorityType>::system(const std::string name) const {
        auto index = m_system_registry.at(name);
        return *m_systems.at(index.first).at(index.second).system;
    }
    template<typename SystemType, typename PriorityType>
    void SystemManager<SystemType, PriorityType>::update() {}
}
#endif // BINTJEKIT_ECS_I_SYSTEM_MANAGER_INL
