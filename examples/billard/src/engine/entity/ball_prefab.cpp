/*!
 * @author bintjeman
 * @date 19.07.25
 * @name ball_prefab.cpp
 */
#include "ball_prefab.hpp"
#include <entt/entt.hpp>
#include <SFML/System/Vector2.hpp>
#include <bintjekit/utils/fmt_sfml/fmt_sfml.hpp>
#include <bintjekit/utils/random/random_engine.hpp>
#include <bintjekit/configuration/node.hpp>

#include "bintjekit/core/core.hpp"
#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/utils/d2/d2.hpp"
#include "engine/billard.hpp"
#include "engine/components/entity.hpp"
#include "engine/components/position_component.hpp"
#include "engine/components/radius_component.hpp"
#include "engine/components/velocity_compponent.hpp"

namespace bil {
    void BallPrefab::initialise(const bnjkit::engine::IEngine& engine, bnjkit::conf::Node node) {
        auto logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::ENTITY);
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
        sf::Vector2f new_size(
            std::max(0.0f, billard_bounds.size.x - m_radius * 2.0f),
            std::max(0.0f, billard_bounds.size.y - m_radius * 2.0f)
        );
        m_bounds = sf::Rect<float>(new_position, new_size);
        logger->debug("Calculated spawn bounds: pos:({}), size:({})",
                      m_bounds.position,
                      m_bounds.size);
        initialise_spawner();
    }
    void BallPrefab::initialise_spawner() {
        spawn = [*this](bnjkit::engine::IEngine& engine) -> entt::entity {
            auto logger = bnjkit::logger::Logger::get_logger(bnjkit::literals::logger::ENTITY);
            const auto billard = dynamic_cast<Billard*>(& engine);
            const auto entity = billard->registry().create();
            auto randomposition = [](const sf::Rect<float>& bounds) {
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
                return entt::null;
            }
            sf::Vector2f position = randomposition(m_bounds);
            billard->registry().emplace<components::PositionComponent>(entity, position);
            billard->registry().emplace<components::RadiusComponent>(entity, m_radius);
            billard->registry().emplace<components::BallFlag>(entity);
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
                auto velocity = [angle, speed]() {
                    const float a = angle();
                    auto s = speed();
                    return sf::Vector2f(std::cos(a) * s, std::sin(a) * s);
                };
                billard->registry().emplace<components::VelocityComponent>(entity, velocity());
            }
            logger->trace("Position between: {} and {}", m_bounds.position, m_bounds.position + m_bounds.size);
            logger->trace("Entity position: ({}, {})", position.x, position.y);
            logger->trace("Entity radius: {}", m_radius);
            logger->trace("Entity speed: {}", m_speed_max);
            return entity;
        };
    }
}
