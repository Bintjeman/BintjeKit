/*!
 * @author bintjeman
 * @date 26.06.25
 * @name evobotengine.hpp
 */
#ifndef EVO_EVOBOTENGINE_HPP
#define EVO_EVOBOTENGINE_HPP
#pragma once
#include <bintjekit/engine.hpp>

namespace evo::engine {
    class EvoWorld;
    class EvobotEngine final : public bnjkit::engine::IEngine {

    public:
        EvobotEngine();
        ~EvobotEngine() override;
        void configure() override;
        void new_world();
        void clear();
        void update() override;
        EvoWorld* get_world();
        const EvoWorld* get_world() const;
        [[nodiscard]] std::string name() const override;
        void on_sfml_event(const sf::Event& event) override;

    private:
        std::unique_ptr<EvoWorld> m_evo_world;
    };
}

#endif // EVO_EVOBOTENGINE_HPP
