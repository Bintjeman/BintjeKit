/*!
* @author bintjeman
 * @date 07.07.25
 * @name evobot_types.hpp
 */

#ifndef EVOBOT_TYPES_HPP
#define EVOBOT_TYPES_HPP
#pragma once

#include "bintjekit/entity/entity_manager.hpp"
#include "evobot.hpp"
#include "glob.hpp"

namespace evo {
    // Définition des types logiques si nécessaire
    // template<>
    // struct bnjkit::entity::RegisteredLogicalBase<Evobot2> {
    //     using type = engine::Evobot;
    // };

    // Type alias pour le gestionnaire d'entités spécifique à Evobot
    using GameEntityManager = bnjkit::entity::EntityManager<engine::Evobot, engine::Glob>;
}

#endif
