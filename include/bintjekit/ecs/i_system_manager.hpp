/*!
 * @author bintjeman
 * @date 16.07.25
 * @name i_system_manager.hpp
 */
#ifndef BINTJEKIT_ECS_I_SYSTEM_MANAGER_HPP
#define BINTJEKIT_ECS_I_SYSTEM_MANAGER_HPP
#pragma once
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include <spdlog/fwd.h>
namespace bnjkit::engine {
    class IEngine;
}
namespace bnjkit::ecs {
    /*!
     * Structure aidant la gestion des @ref bnjkit::ecs::ISystem avec des métadonnées utiles.
     *
     * @tparam SystemType Le type de sous-system (par exemple @ref bnjkit::renderer::RenderSystemManager)
     */
    template<typename SystemType>
    struct SystemEntry {
        SystemEntry(std::unique_ptr<SystemType> sys, std::string n = {}, bool e = true);
        std::unique_ptr<SystemType> system;
        std::string name;
        bool enabled;
    };
    /*!
     * Class permettant de gérer l'enregistrement de systèmes utiles pour la manipulation des composants et entité ECS (entt).
     *
     * @tparam SystemType Donne la possibilité de redéfinir la façon dont le gestionnaire de systèmes gère les priorités.
     * @tparam PriorityType Le type de sous-system (par exemple @ref bnjkit::renderer::RenderSystemManager)
     */
    template<typename SystemType, typename PriorityType>
    class SystemManager {
    public:
        using Entry = SystemEntry<SystemType>;
        SystemManager();
        virtual ~SystemManager();
        virtual void initialise();
        virtual void configure();
        virtual void on_quit();
        // Gestion des systèmes
        virtual void add_system(std::unique_ptr<SystemType> system, PriorityType priority);
        virtual bool remove_system(const std::string& name);
        virtual void clear();
        virtual void toggle_system(const std::string& name, bool enable);
        virtual SystemType& system(const std::string& name);
        virtual const SystemType& system(std::string name) const;
        // Mise à jour
        virtual void update(engine::IEngine& engine);

    protected:
        std::map<PriorityType, std::vector<Entry> > m_systems;
        std::unordered_map<std::string, std::pair<PriorityType, std::size_t> > m_system_registry;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#include "i_system_manager.inl"
#endif // BINTJEKIT_ECS_I_SYSTEM_MANAGER_HPP
