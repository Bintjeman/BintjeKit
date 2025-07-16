/*!
 * @author bintjeman
 * @date 26.06.25
 * @name evobotengine.hpp
 */
#ifndef EVO_EVOBOTENGINE_HPP
#define EVO_EVOBOTENGINE_HPP
#pragma once
#include <bintjekit/engine/i_engine.hpp>
namespace sf {
    class Event;
}
namespace evo::engine {
    class EvobotEngine final : public bnjkit::engine::IEngine {
    public:
        EvobotEngine();
        ~EvobotEngine() override;
        void configure() override;
        void initialise() override;
        void new_world();
        [[nodiscard]] std::string name() const override;
        void on_sfml_event(const sf::Event& event) override;

    };
}

#endif // EVO_EVOBOTENGINE_HPP
