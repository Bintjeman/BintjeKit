/*!
 * @author bintjeman
 * @date 13.07.25
 * @name evo_world.hpp
 */

/*!
 * @author bintjeman
 * @date 13.07.25
 * @name evo_world.hpp
 */

#ifndef EVOBOT_ENGINE_EVO_WORLD_HPP
#define EVOBOT_ENGINE_EVO_WORLD_HPP
#pragma once

#include <bintjekit/engine/world.hpp>
#include "bintjekit/configuration/node.hpp"
namespace evo::engine {
    class EvoWorld final : public bnjkit::engine::World {
    public:
        explicit EvoWorld();
        ~EvoWorld() override;
        void initialization();
        void init_prefab();
        // Configuration spécifique au monde Evo
        void set_settings(bnjkit::conf::Node& settings);
        void configure(bnjkit::conf::Node settings = bnjkit::conf::Node{});
        void generate();

        // Accès aux paramètres du monde
        float get_bot_min_radius() const { return m_bot_min_radius; }
        float get_bot_max_radius() const { return m_bot_max_radius; }
        float get_bot_max_speed() const { return m_bot_max_speed; }
        float get_glob_min_radius() const { return m_glob_min_radius; }
        float get_glob_max_radius() const { return m_glob_max_radius; }
        float get_glob_max_speed() const { return m_glob_max_speed; }
        unsigned int get_minimum_bot() const { return m_minimum_bot; }
        unsigned int get_maximum_bot() const { return m_maximum_bot; }
        unsigned int get_minimum_glob() const { return m_minimum_glob; }
        unsigned int get_maximum_glob() const { return m_maximum_glob; }

    private:
        bnjkit::conf::Node m_settings;
        void generate_playground();
        // Paramètres du monde
        float m_bot_min_radius{1.f};
        float m_bot_max_radius{10.f};
        float m_bot_max_speed{10.f};
        float m_glob_min_radius{1.f};
        float m_glob_max_radius{10.f};
        float m_glob_max_speed{10.f};
        unsigned int m_minimum_bot{0};
        unsigned int m_maximum_bot{10};
        unsigned int m_minimum_glob{0};
        unsigned int m_maximum_glob{10};
    };

} // namespace evo::engine

#endif // EVOBOT_ENGINE_EVO_WORLD_HPP
