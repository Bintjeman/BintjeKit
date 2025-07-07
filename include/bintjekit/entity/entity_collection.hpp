/*!
 * @author bintjeman
 * @date 07.07.25
 * @name entity_collection.hpp
 */
#ifndef ENTITY_COLLECTION_HPP
#define ENTITY_COLLECTION_HPP
#pragma once
#include <type_traits>
#include <vector>
#include <spdlog/fwd.h>
#include "bintjekit/entity/entity_helper.hpp"
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    template<typename BaseEntity>
        requires std::is_base_of_v<IEntity, BaseEntity>
    class EntityCollectionManager {
    public:
        EntityCollectionManager();
        ~EntityCollectionManager() = default;

        void add(const EntityPtr& entity);
        EntityPtr create(EntityId id);
        EntityPtr get(EntityId id);
        const EntityPtr get(EntityId id) const;
        void remove(EntityId id);
        void clear();
        [[nodiscard]] std::size_t size() const;
        [[nodiscard]] EntityCollection get_entities() const;
        [[nodiscard]] EntityCollection get_entities();
        [[nodiscard]] EntityRegistry get_registry() const;
        [[nodiscard]] EntityRegistry get_registry();

    private:
        EntityCollection m_entities;
        EntityRegistry m_registry;
        static std::shared_ptr<spdlog::logger> m_logger;
    };
}

#include "entity_collection.inl"

#endif //ENTITY_COLLECTION_HPP
