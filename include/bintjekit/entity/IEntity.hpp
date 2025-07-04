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
namespace bnjkit {
    namespace entity {
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
            static EntityId total_entities();
            static void set_logger(const std::shared_ptr<spdlog::logger>& logger);
        protected:
            static EntityId next_id();
            EntityId m_id;
            static std::shared_ptr<spdlog::logger> s_logger;
            static EntityId s_total_entities;
            static EntityId s_next_id;
            static constexpr EntityId INVALID_ID = std::numeric_limits<EntityId>::max();
        }; // Entity
    } // entity
} // bnjkit

#endif // BINJTJEKIT_ENTITY_ENTITY_HPP
