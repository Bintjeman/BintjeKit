/*!
 * @author bintjeman
 * @date 12.07.25
 * @name entity_manager_builder.cpp
 */

#include "entity_manager_builder.hpp"

#include "entity_manager.hpp"
#include "evobot.hpp"
#include "glob.hpp"

namespace evo__entity {
} // evo__entity
void evo::entity::EntityManagerBuilder::setup_default_collections(EvoEntityManager& manager) {
    manager.create_collection<engine::Glob>();
    manager.create_collection<engine::Evobot>();
}
void evo::entity::EntityManagerBuilder::setup_default_components(EvoEntityManager& manager) {}
void evo::entity::EntityManagerBuilder::build_default(EvoEntityManager& manager) {
    setup_default_collections(manager);
    setup_default_components(manager);
}
