/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entity.cpp
 */
#include <utility>
#include <spdlog/spdlog.h>
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit {
    namespace entity {
        std::size_t IEntity::s_next_id = 0;
        std::size_t IEntity::s_total_entities = 0;
        std::shared_ptr<spdlog::logger> IEntity::s_logger;
        IEntity::IEntity() : m_id(next_id()) {
            ++ s_total_entities;
        }
        IEntity::IEntity(const IEntity&) : m_id(next_id()) {
            ++ s_total_entities;
        }
        IEntity& IEntity::operator=(const IEntity& other) noexcept {
            if (this != & other) {
                // Garder notre ID, ne pas copier celui de other
                // Pas besoin de modifier s_total_entities car l'entité existe déjà
            }
            return * this;
        }
        IEntity::IEntity(IEntity&& other) noexcept : m_id(INVALID_ID) {
            std::swap(m_id, other.m_id);
        }
        IEntity& IEntity::operator=(IEntity&& other) noexcept {
            if (this != & other) {
                // Si cette entité était valide, on la marque comme invalide
                if (m_id != INVALID_ID) {
                    -- s_total_entities;
                }
                m_id = INVALID_ID;
                std::swap(m_id, other.m_id);
            }
            return * this;
        }
        IEntity::~IEntity() {
            if (m_id != INVALID_ID) {
                // Ne décrémenter que si l'entité était valide
                -- s_total_entities;
            }
        }
        std::size_t IEntity::id() const {
            if (!valid()) {
                s_logger->error("Attempting to get ID of invalid entity");
                throw std::runtime_error("Attempting to get ID of invalid entity");
            }
            return m_id;
        }
        bool IEntity::valid() const {
            return m_id != INVALID_ID;
        }
        std::size_t IEntity::next_id() {
            return s_next_id++;
        }
        std::size_t IEntity::total_entities() {
            return s_total_entities;
        }
        void IEntity::set_logger(const std::shared_ptr<spdlog::logger>& logger) {
            s_logger = logger;
        }
    } // entity
} // bnjkit
