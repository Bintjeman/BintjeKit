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
#include "bintjekit/entity/i_entity_collection_manager.hpp"
namespace bnjkit::entity {
    template<typename T>
        requires std::is_base_of_v<IEntity, T>
    class EntityCollectionManager : public IEntityCollectionManager {
    public:
        EntityCollectionManager();
        ~EntityCollectionManager() override = default;

        void add(const EntityPtr& entity);
        EntityPtr create();
        EntityPtr get(EntityId id);
        const EntityPtr get(EntityId id) const;
        void remove(EntityId id) override;
        void clear() override;
        [[nodiscard]] std::size_t size() const;
        [[nodiscard]] EntityCollection get_entities() const;
        [[nodiscard]] EntityCollection get_entities() override;
        [[nodiscard]] EntityRegistry get_registry() const;
        [[nodiscard]] EntityRegistry get_registry();
        static void set_logger(const std::shared_ptr<spdlog::logger>& logger);
    private:
        EntityCollection m_entities;
        EntityRegistry m_registry;
        static std::shared_ptr<spdlog::logger> m_logger;
    };
}

#include "entity_collection.inl"

#endif //ENTITY_COLLECTION_HPP
