/*!
 * @author bintjeman
 * @date 19.07.25
 * @name billard.cpp
 */

#include "billard.hpp"
#include <SFML/System/Vector2.hpp>
#include <bintjekit/configuration/node.hpp>
#include <bintjekit/configuration/json_adapter.hpp>

#include "bintjekit/engine/play_ground.hpp"
#include "components/entity.hpp"
#include "components/position_component.hpp"
#include "entity/ball_prefab.hpp"

namespace bil {
    Billard::Billard() {
        m_logger->info("BillardEngine created");
    }

    Billard::~Billard() {
        m_logger->info("BillardEngine destroyed");
    }

    void Billard::configure() {
        m_logger->trace("BillardEngine configuration");
        const auto node = m_settings.root().create_child("/Billard"_json_pointer);
        set_custom(node);
        const auto orientation = m_custom_settings.get_or_set("/Orientation", std::string("Vertical"));
        auto size = m_custom_settings.get_or_set("/Size",
                                                 sf::Vector2f{2090, 1190}
        );
        // Configure
        auto x = size.x;
        auto y = size.y;
        if (orientation == "Vertical") {
            if (std::max(x, y) == x) {
                std::swap(x, y);
            }
        } else {
            if (std::min(x, y) == x) {
                std::swap(x, y);
            }
        }
        size = sf::Vector2f{x, y};
        const auto position = size / 2.0f;
        m_play_ground->set_bounds(position, size);
        m_max_ball = m_custom_settings.get_or_set("/Rules/Maximum balls", 25ul);
        m_min_ball = m_custom_settings.get_or_set("/Rules/Minimum balls", 5ul);
        BallPrefab prefab_ball;
        prefab_ball.initialise(* this, m_custom_settings.create_child("/Prefab ball"_json_pointer));
        register_prefab("aleaball", static_cast<bnjkit::ecs::PrefabData>(prefab_ball));
        m_logger->debug("PlayGround configured with size: ({}, {})", size.x, size.y);
    }

    void Billard::add_ball() {
        auto balls_view = registry().view<components::BallFlag>();
        if (balls_view.size() < m_max_ball) {
            spawn_prefab("aleaball");
        }
    }

    void Billard::update() {
        auto balls_view = registry().view<components::BallFlag>();
        if (balls_view.size() < m_min_ball) {
            add_ball();
        }
        if (balls_view.size() > m_max_ball) {}
    }

    std::string Billard::name() const {
        return "BillardEngine";
    }
} // bil
