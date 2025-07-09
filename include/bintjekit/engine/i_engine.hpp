/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.hpp
 */
#ifndef BNJKIT_ENGINE_I_ENGINE_HPP
#define BNJKIT_ENGINE_I_ENGINE_HPP
#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include <spdlog/fwd.h>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"
#include "bintjekit/entity/ientity.hpp"

namespace bnjkit {
    namespace entity {
        class EntityManager;
    }

    namespace engine {
        struct PlayGround;

        class IEngine : public core::IModule, public event::IEventListener {
        public:
            using BaseEntity = entity::IEntity;

            enum class State {
                READY,
                FINISH,
                EMPTY,
            };

            IEngine();
            ~IEngine() override;
            void initialise() override;
            void configure() override;
            virtual void update();
            [[nodiscard]] PlayGround& play_ground() const;
            [[nodiscard]] State state() const;

        protected:
            State m_state{State::EMPTY};
            std::unique_ptr<PlayGround> m_play_ground;
            std::unique_ptr<entity::EntityManager > m_entity_manager;
            std::shared_ptr<spdlog::logger> m_logger;

        public:
            static std::string state_to_string(State state);
            void on_sfml_event(const sf::Event& event) override;
            [[nodiscard]] std::string name() const override;
        };
    } // engine
} // bnjkit

#endif // BNJKIT_ENGINE_I_ENGINE_HPP
