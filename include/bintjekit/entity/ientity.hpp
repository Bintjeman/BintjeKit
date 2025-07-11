/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity.hpp
 */
#ifndef BINJTJEKIT_ENTITY_ENTITY_HPP
#define BINJTJEKIT_ENTITY_ENTITY_HPP
#pragma once
#include <limits>
#include <memory>
#include <spdlog/fwd.h>

namespace bnjkit::entity {
    enum class EntityState {
        ACTIVE,
        DEAD,
        DISABLED
    };
    using EntityId = std::size_t;
    class IEntity {
    public:
        IEntity();
        virtual ~IEntity();
        IEntity(const IEntity&);
        IEntity& operator=(const IEntity& other) noexcept;
        IEntity(IEntity&& other) noexcept;
        IEntity& operator=(IEntity&& other) noexcept;
        [[nodiscard]] EntityId id() const;
        [[nodiscard]] bool valid() const;
        [[nodiscard]] EntityState state() const;
        void set_state(EntityState state);
        [[nodiscard]] bool is_active() const;
        [[nodiscard]] bool is_dead() const;
        [[nodiscard]] bool is_disabled() const;
        virtual void update();
        static EntityId total_entities();
        static void set_logger(const std::shared_ptr<spdlog::logger>& logger);

    protected:
        static EntityId next_id();
        EntityId m_id;
        EntityState m_state;
        static std::shared_ptr<spdlog::logger> m_s_logger;
        static EntityId m_s_total_entities;
        static EntityId m_s_next_id;
        static constexpr EntityId s_invalid_id = std::numeric_limits<EntityId>::max();
    }; // Entity
}

#endif // BINJTJEKIT_ENTITY_ENTITY_HPP
