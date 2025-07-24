/*!
 * @author bintjeman
 * @date 24.07.25
 * @name ball_init_system.cpp
 */

#include "ball_init_system.hpp"
#include <bintjekit/utils/fmt_sfml/fmt_sfml.hpp>
#include <bintjekit/logger.hpp>
#include <bintjekit/engine/play_ground.hpp>

#include "bintjekit/utils/d2/d2.hpp"
#include "bintjekit/utils/random/random_engine.hpp"
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"
#include "engine/components/position_component.hpp"
#include "engine/components/radius_component.hpp"
#include "engine/components/velocity_compponent.hpp"

namespace bil {
    BallInitSystem::~BallInitSystem() = default;
    void BallInitSystem::configuration(bnjkit::engine::IEngine& engine, bnjkit::conf::Node node) {
        const auto logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::ENTITY);
        const auto billard = dynamic_cast<const Billard*>(& engine);
        if (!billard) {
            logger->error("Failed to cast engine to Billard");
            return;
        }
        m_radius = node.get_or_set("/Radius", 10.0f);
        m_speed_max = node.get_or_set("/Speed max", 2.0f);
        const auto billard_bounds = billard->play_ground().bounds();
        logger->debug("Original billard bounds: pos:({}), size:({})",
                      billard_bounds.position, billard_bounds.size);
        // Vérification des valeurs
        if (billard_bounds.size.x <= 0 || billard_bounds.size.y <= 0) {
            logger->error("Invalid billard bounds size");
            return;
        }
        // Construction des bornes pour le spawn avec vérification
        sf::Vector2f new_position(
            billard_bounds.position.x + m_radius,
            billard_bounds.position.y + m_radius
        );
        const sf::Vector2f new_size(
            std::max(0.0f, billard_bounds.size.x - m_radius * 2.0f),
            std::max(0.0f, billard_bounds.size.y - m_radius * 2.0f)
        );
        m_bounds = sf::Rect<float>(new_position, new_size);
        logger->debug("Calculated spawn bounds: pos:({}), size:({})",
                      m_bounds.position,
                      m_bounds.size);
    }
    void BallInitSystem::update(bnjkit::engine::IEngine& engine) {
        const auto logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::ENTITY);
        const auto billard = dynamic_cast<Billard*>(& engine);
        auto& registry = billard->registry();
        auto random_position = [](const sf::Rect<float>& bounds) {
            const float x = bnjkit::utils::random::RandomEngine::get_float(bounds.position.x,
                                                                           bounds.position.x + bounds.size.x
            );
            const float y = bnjkit::utils::random::RandomEngine::get_float(bounds.position.y,
                                                                           bounds.position.y + bounds.size.y
            );
            return sf::Vector2f(x, y);
        };
        if (m_bounds.size.x < 0.0f || m_bounds.size.y < 0.0f) {
            logger->error("Bounds size is negative");
            return;
        }
        sf::Vector2f position = random_position(m_bounds);
        sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f);
        if (m_speed_max > 0.0f) {
            auto angle = []() {
                return bnjkit::utils::random::RandomEngine::get_float(
                    0.0f,
                    bnjkit::utils::d2::PIX2 - std::numeric_limits<float>::epsilon()
                );
            };
            auto speed = [m_speed_max = m_speed_max]() {
                return bnjkit::utils::random::RandomEngine::get_float(0.0f, m_speed_max);
            };
            const float a = angle();
            auto s = speed();
            velocity = sf::Vector2f(std::cos(a) * s, std::sin(a) * s);
        } else {
            velocity = sf::Vector2f(0.0f, 0.0f);
        }
        auto needs_init_view = billard->registry().view<components::NeedsInitMark>();
        needs_init_view.each([this,&registry, &position, &velocity, &logger](const auto& entity_tag) {
            auto& pos = registry.get<components::PositionComponent>(entity_tag);
            auto& vel = registry.get<components::VelocityComponent>(entity_tag);
            auto& rad = registry.get<components::RadiusComponent>(entity_tag);
            pos.position = position;
            vel.velocity = velocity;
            rad.radius = m_radius;
            registry.remove<components::NeedsInitMark>(entity_tag);
            logger->trace("Entity spawned at ({}, {})", position.x, position.y);
        });
        logger->trace("Position between: {} and {}", m_bounds.position, m_bounds.position + m_bounds.size);
        logger->trace("Entity position: ({}, {})", position.x, position.y);
        logger->trace("Entity radius: {}", m_radius);
        logger->trace("Entity speed: {}", m_speed_max);
    }
    std::string BallInitSystem::name() const {
        return "Ball init system";
    }
} // bil
