/*!
 * @author bintjeman
 * @date 26.06.25
 * @name evobotengine.hpp
 */
#ifndef EVO_EVOBOTENGINE_HPP
#define EVO_EVOBOTENGINE_HPP
#pragma once
#include <bintjekit/engine.hpp>
#include <bintjekit/entity/entity_manager.hpp>
#include "entity.hpp"

namespace evo::engine {
    class EvobotEngine final : public bnjkit::engine::IEngine {
        using Entity = bnjkit::entity::IEntity;

    public:
        EvobotEngine();
        ~EvobotEngine() override;
        void configure() override;
        void new_world();
        void clear();
        void update() override;
        [[nodiscard]] auto entities() const;
        bnjkit::entity::EntityManager<Entity>& entity_manager();
        [[nodiscard]] const bnjkit::entity::EntityManager<Entity>& entity_manager() const;
        [[nodiscard]] std::string name() const override;
        void on_sfml_event(const sf::Event& event) override;

    private:
        unsigned int m_minimum_bot{0};
        unsigned int m_maximum_bot{10};
        unsigned int m_minimum_glob{0};
        unsigned int m_maximum_glob{10};
        float m_bot_min_radius{1.f};
        float m_bot_max_radius{10.f};
        float m_bot_max_speed{2.f};
        float m_glob_min_radius{1.f};
        float m_glob_max_radius{10.f};
        float m_glob_max_speed{1.f};
    };
}

#endif // EVO_EVOBOTENGINE_HPP
