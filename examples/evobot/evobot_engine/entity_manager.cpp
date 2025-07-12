/*!
 * @author bintjeman
 * @date 11.07.25
 * @name entity_manager.cpp
 */

#include "entity_manager.hpp"

#include "evobot_engine/entity_manager_builder.hpp"

namespace evo::entity {
    EvoEntityManager::EvoEntityManager() {
        init();
    }
    EvoEntityManager::~EvoEntityManager() = default;
    void EvoEntityManager::init() {
        EntityManagerBuilder::build_default(* this);
    }
}
