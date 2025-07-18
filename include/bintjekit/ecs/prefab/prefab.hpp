/*!
 * @author bintjeman
 * @date 13.07.25
 * @name prefab.hpp
 */

#ifndef BINTJEKIT_ESC_PREFAB_HPP
#define BINTJEKIT_ESC_PREFAB_HPP
#pragma once
#include <functional>
#include <entt/entity/entity.hpp>

namespace bnjkit::engine {
    class IEngine;
}

namespace bnjkit::ecs {
    /**
     * @class PrefabData
     * @brief A class representing the data structure and associated information for a prefab.
     *
     * The PrefabData class is designed to encapsulate all data relevant to a prefab,
     * which is a reusable asset or template used within a system, such as in game development
     * or other design contexts. It provides a framework for accessing and managing data
     * like identifier, metadata, and other related properties that describe or configure
     * the prefab instance.
     *
     * Key responsibilities of this class include:
     * - Managing and providing access to the core information about the prefab.
     * - Allowing extensions or customization through additional fields or metadata.
     * - Serving as an abstraction layer between the raw prefab configuration data and the user.
     *
     * This class is intended to simplify the handling and organization of prefab-related
     * content within a larger application or toolchain.
     */
    class PrefabData {
        public:
        // Fonction générique de spawn qui retourne une entité
        std::function<entt::entity(engine::IEngine &)> spawn;
        // Métadonnées optionnelles (utile pour le debugging/logging)
        std::string name;
    };
}

#endif // BINTJEKIT_ESC_PREFAB_HPP
