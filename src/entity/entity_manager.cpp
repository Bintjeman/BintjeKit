/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_manager.cpp
 */

#include "bintjekit/entity/entity_manager.hpp"
#include <bintjekit/logger/logger.hpp>
#include "bintjekit/core/common.hpp"

namespace bnjkit::entity {
    EntityManager::EntityManager() {
        m_logger = core::Logger::get_logger(bnjkit::core::module_names::ENTITY);
    }
    EntityManager::~EntityManager() {}
    void EntityManager::clear() {
        m_collections.clear();
        m_entity_types.clear();
    }
    std::size_t EntityManager::size() const {
        std::size_t size = 0;
        for (const auto& collection: m_collections) {
            size += collection.second->size();
        }
        return size;
    }
}
