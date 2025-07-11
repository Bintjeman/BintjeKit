/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity.cpp
 */
// #include <utility>
#include <spdlog/spdlog.h>
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit::entity {
    std::size_t IEntity::m_s_next_id = 0;
    std::size_t IEntity::m_s_total_entities = 0;
    std::shared_ptr<spdlog::logger> IEntity::m_s_logger;
    IEntity::IEntity() : m_id(next_id()), m_state(EntityState::ACTIVE) {
        ++ m_s_total_entities;
    }
    IEntity::IEntity(const IEntity&) : m_id(next_id()), m_state(EntityState::ACTIVE) {
        ++ m_s_total_entities;
    }
    IEntity& IEntity::operator=(const IEntity& other) noexcept {
        if (this != & other) {
            m_id = other.m_id;
            m_state = other.m_state;
        }
        return * this;
    }
    IEntity::IEntity(IEntity&& other) noexcept : m_id(other.m_id), m_state(other.m_state) {
        other.m_id = s_invalid_id;
        other.m_state = EntityState::DISABLED;
    }
    IEntity& IEntity::operator=(IEntity&& other) noexcept {
        if (this != & other) {
            if (m_id != s_invalid_id) {
                -- m_s_total_entities;
            }
            m_id = other.m_id;
            m_state = other.m_state;
            other.m_id = s_invalid_id;
            other.m_state = EntityState::DISABLED;
        }
        return * this;
    }
    IEntity::~IEntity() {
        if (m_id != s_invalid_id) {
            // Ne décrémenter que si l'entité était valide
            -- m_s_total_entities;
        }
    }
    std::size_t IEntity::id() const {
        if (!valid()) {
            m_s_logger->error("Attempting to get ID of invalid entity");
            throw std::runtime_error("Attempting to get ID of invalid entity");
        }
        return m_id;
    }
    bool IEntity::valid() const {
        return m_id != s_invalid_id;
    }
    EntityState IEntity::state() const {
        return m_state;
    }
    void IEntity::set_state(const EntityState state) {
        m_state = state;
    }
    bool IEntity::is_active() const {
        return m_state == EntityState::ACTIVE;
    }
    bool IEntity::is_dead() const {
        return m_state == EntityState::DEAD;
    }
    bool IEntity::is_disabled() const {
        return m_state == EntityState::DISABLED;
    }
    void IEntity::update() {}
    std::size_t IEntity::next_id() {
        return m_s_next_id++;
    }
    std::size_t IEntity::total_entities() {
        return m_s_total_entities;
    }
    void IEntity::set_logger(const std::shared_ptr<spdlog::logger>& logger) {
        m_s_logger = logger;
    }
}
