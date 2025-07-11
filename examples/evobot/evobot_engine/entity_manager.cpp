/*!
 * @author bintjeman
 * @date 11.07.25
 * @name entity_manager.cpp
 */

#include "entity_manager.hpp"
#include "components/arrow_component.hpp"
#include "components/health.hpp"
#include "evobot_engine/evobot.hpp"
#include "evobot_engine/glob.hpp"

namespace evo {
    namespace entity {
        EvoEntityManager::EvoEntityManager() {
            init();
        }
        EvoEntityManager::~EvoEntityManager() {}
        void EvoEntityManager::init() {
            create_collection<engine::Glob>();
            create_collection<engine::Evobot>();
            register_component<ArrowComponent>();
            register_component<Health>();
        }
    } // entity
} // evo
