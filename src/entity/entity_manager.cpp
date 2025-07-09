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
    void EntityManager::remove(const EntityId id){
        if (m_entity_types.contains(id)) {
            const auto entity_type = m_entity_types.find(id)->second;
            if (m_collections.contains(entity_type)) {
                auto& collection = * static_cast<TypedCollection<IEntity>*>(m_collections.at(entity_type)
                    .get());
                collection.remove(id);
            }
            m_logger->warn("Collection {} does not exist", entity_type.name());
        }
        m_logger->warn("Entity {} does not exist", id);
    }
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
