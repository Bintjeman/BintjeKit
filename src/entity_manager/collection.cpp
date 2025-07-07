/*!
 * @author bintjeman
 * @date 26.06.25
 * @name collection.cpp
 */
#include "bintjekit/core/common.hpp"
#include "bintjekit/entity/collection.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::entity {
    Collection::Collection() {
        m_logger = core::Logger::get_logger(core::module_names::ENTITY);
    }
    Collection::~Collection() = default;
    void Collection::add_entity(const std::shared_ptr<IEntity>& entity) {
        if (!entity || !entity->valid()) {
            m_logger->error("Cannot add invalid entity");
            throw std::invalid_argument("Cannot add invalid entity");
        }
        auto index = m_collection.size();
        m_collection.push_back(entity);
        m_registry.emplace(entity->id(), index);
    }
    void Collection::remove_entity(const EntityPtr& entity) {
        if (!entity || !entity->valid()) {
            m_logger->error("Cannot remove invalid entity");
            throw std::invalid_argument("Cannot remove invalid entity");
        }
        remove_entity(entity->id());
    }
    void Collection::remove_entity(EntityId id) {
        auto it = m_registry.find(id);
        if (it != m_registry.end()) {
            m_collection[it->second] = std::move(m_collection.back());
            m_collection.pop_back();
            m_registry.erase(id);
        }
    }
    void Collection::clear() {
        m_collection.clear();
        m_registry.clear();
    }
    EntityCollection& Collection::get_collection() {
        return m_collection;
    }
    const EntityCollection& Collection::get_collection() const {
        return m_collection;
    }
    EntityRegystry& Collection::get_registry() {
        return m_registry;
    }
    std::shared_ptr<IEntity> Collection::get_entity(EntityId id) {
        auto it = m_registry.find(id);
        if (it != m_registry.end()) {
            return m_collection[it->second];
        }
        m_logger->error("Entity not found");
        throw std::runtime_error("Entity not found");
    }
    EntityIndex Collection::get_entity_index(EntityId id) {
        const auto it = m_registry.find(id);
        return it->second;
    }
}
