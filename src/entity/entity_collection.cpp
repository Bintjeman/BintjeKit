/*!
 * @author bintjeman
 * @date 08.07.25
 * @name entity_collection.cpp
 */

#include "bintjekit/entity/entity_collection.hpp"
#include "bintjekit/entity/components/component_view.hpp"

namespace bnjkit::entity {
    EntityCollection::ViewBuilder::ViewBuilder(const EntityCollection& collection)
        : m_collection(collection) {}

    EntityCollection::ViewBuilder& EntityCollection::ViewBuilder::where(
        std::function<bool(const EntityPtr&)> filter) {
        m_filter = std::move(filter);
        return * this;
    }

    ComponentView<IEntity> EntityCollection::ViewBuilder::build() {
        return {m_collection, m_filter};
    }

    void EntityCollection::add(const EntityPtr& entity) {
        if (!entity) return;
        const auto id = entity->id();
        m_entities.push_back(entity);
        m_registry[id] = m_entities.size() - 1;
    }

    void EntityCollection::remove(const EntityId id) {
        const auto it = m_registry.find(id);
        if (it == m_registry.end()) return;

        const std::size_t index = it->second;
        if (const std::size_t last_index = m_entities.size() - 1; index != last_index) {
            m_entities[index] = m_entities[last_index];
            m_registry[m_entities[index]->id()] = index;
        }

        m_entities.pop_back();
        m_registry.erase(it);
    }

    EntityCollection::EntityPtr EntityCollection::get(const EntityId id) const {
        const auto it = m_registry.find(id);
        if (it == m_registry.end()) return nullptr;
        return m_entities[it->second];
    }
    void EntityCollection::clear() {
        m_entities.clear();
        m_registry.clear();
    }
}
