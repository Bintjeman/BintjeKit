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

namespace bnjkit::ecs {
    class IWorld;
}

namespace bnjkit::ecs {
    class PrefabData {
        public:
        // Fonction générique de spawn qui retourne une entité
        std::function<entt::entity(IWorld &)> spawn;
        // Métadonnées optionnelles (utile pour le debugging/logging)
        std::string name;
    };
}

#endif // BINTJEKIT_ESC_PREFAB_HPP
