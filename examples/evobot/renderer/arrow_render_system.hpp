/*!
 * @author bintjeman
 * @date 10.07.25
 * @name arrow_render_system.hpp
 */

#ifndef ARROW_RENDER_SYSTEM_HPP
#define ARROW_RENDER_SYSTEM_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Angle.hpp>
#include <bintjekit/entity/entity_manager.hpp>
#include "evobot_engine/evobot.hpp"
#include "evobot_engine/components/arrow_component.hpp"
#include "arrow_render_system.hpp"

namespace evo::renderer {
    class ArrowRenderSystem {
    public:
        static sf::RectangleShape make_line(engine::Evobot& evobot, const entity::ArrowComponent& arrow) {
            sf::RectangleShape line({arrow.length, 2.0f});
            // Position de l'Evobot
            auto position = evobot.position();
            // Direction de l'Evobot (à adapter selon votre implémentation)
            float angle = std::atan2(evobot.velocity().y, evobot.velocity().x);
            line.setPosition(position);
            line.setRotation(sf::degrees(angle * 180.0f / std::numbers::pi_v<float>
            ));
            line.setFillColor(arrow.color);
            return line;
        }
        static sf::ConvexShape make_head(engine::Evobot& evobot, const entity::ArrowComponent& arrow) {
            sf::ConvexShape head;
            head.setPointCount(3);
            head.setPoint(0, {0, - 5});
            head.setPoint(1, {10, 0});
            head.setPoint(2, {0, 5});
            // Position de l'Evobot
            auto position = evobot.position();
            // Direction de l'Evobot (à adapter selon votre implémentation)
            float angle = std::atan2(evobot.velocity().y, evobot.velocity().x);
            head.setPosition({
                position.x + std::cos(angle) * arrow.length,
                position.y + std::sin(angle) * arrow.length
            });
            head.setRotation(sf::degrees(angle * 180.0f / std::numbers::pi_v<float>
            ));
            head.setFillColor(arrow.color);
            return head;
        }
        static void render(sf::RenderTarget& target, const bnjkit::entity::EntityManager& entity_manager) {
            for (const auto& evobots = entity_manager.get_collection<engine::Evobot>(); const auto& evobot: evobots.
                 typed_entities()) {
                if (const auto* arrow = entity_manager.get_component<entity::ArrowComponent>(evobot->id())) {
                    target.draw(make_line(* evobot, * arrow));
                    target.draw(make_head(* evobot, * arrow));
                }
            }
        }
        static void append_drawables(std::vector<std::reference_wrapper<sf::Drawable> >& drawable_list,
                                     const bnjkit::entity::EntityManager& entity_manager) {
            // On stocke les formes quelque part pour qu'elles restent en vie
            static struct DrawableStorage {
                std::vector<sf::RectangleShape> lines;
                std::vector<sf::ConvexShape> heads;
                void clear() {
                    lines.clear();
                    heads.clear();
                }
                void reserve(const size_t size) {
                    lines.reserve(size);
                    heads.reserve(size);
                }
            } storage;
            const auto& evobots = entity_manager.get_collection<engine::Evobot>();
            storage.clear();
            storage.reserve(evobots.entities().size());
            for (const auto& evobot: evobots.typed_entities()) {
                if (const auto* arrow = entity_manager.get_component<entity::ArrowComponent>(evobot->id())) {
                    storage.lines.push_back(make_line(* evobot, * arrow));
                    storage.heads.push_back(make_head(* evobot, * arrow));
                    drawable_list.emplace_back(storage.lines.back());
                    drawable_list.emplace_back(storage.heads.back());
                }
            }
        }
    };
}

#endif //ARROW_RENDER_SYSTEM_HPP
