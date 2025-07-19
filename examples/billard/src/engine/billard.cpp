/*!
 * @author bintjeman
 * @date 19.07.25
 * @name billard.cpp
 */

#include "billard.hpp"
#include <SFML/System/Vector2.hpp>
#include <bintjekit/configuration/json_adapter.hpp>

#include "bintjekit/engine/play_ground.hpp"
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
        auto size = m_custom_settings.get_or_set("/Size", sf::Vector2f{2090, 1190});
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
        m_play_ground->position = position;
        m_play_ground->size = size;
        BallPrefab prefab_ball;
        prefab_ball.initialise();
        register_prefab("aleaball", prefab_ball);
    }
    void Billard::add_ball() {
        for (unsigned int i = 0; i < 1000; i++) {
            spawn_prefab("aleaball");
        }
    }
    std::string Billard::name() const {
        return "BillardEngine";
    }
} // bil
