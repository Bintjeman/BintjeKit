/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.hpp
 */
#ifndef I_ENGINE_HPP
#define I_ENGINE_HPP
#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include "bintjekit/core/i_module.hpp"

namespace bnjkit {
    namespace engine {
        struct PlayGround;
        /**
         * @class IEngine
         * @brief An abstract interface for the engine module within an application system.
         *
         * This class defines the core functionalities that an engine module must provide,
         * including initialization, configuration, event handling, and updating.
         * Derived classes must implement these pure virtual functions.
         */
        class IEngine : public bnjkit::core::IModule {
        public:
            IEngine();
            ~IEngine() override;
            void initialise() override;
            void configure() override;
            virtual void update() = 0;
            virtual void on_sfml_event(const sf::Event &event);
            [[nodiscard]] PlayGround &play_ground() const;

        protected:
            std::unique_ptr<PlayGround> m_play_ground;
        };
    } // engine
} // bnjkit

#endif //I_ENGINE_HPP
