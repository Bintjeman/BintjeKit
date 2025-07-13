/*!
 * @author bintjeman
 * @date 13.07.25
 * @name prefab.hpp
 */

#ifndef BINTJEKIT_ENGINE_PREFAB_HPP
#define BINTJEKIT_ENGINE_PREFAB_HPP
#pragma once
#include <functional>

#include "entt/entity/entity.hpp"

namespace bnjkit::engine {
    class World;
}

namespace bnjkit::engine {
    class PrefabData {
        public:
        // Fonction générique de spawn qui retourne une entité
        std::function<entt::entity(bnjkit::engine::World &)> spawn;
        // Métadonnées optionnelles (utile pour le debugging/logging)
        std::string name;
    };
}

#endif // BINTJEKIT_ENGINE_PREFAB_HPP
