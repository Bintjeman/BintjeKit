/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.cpp
 */

#include "bintjekit/engine/i_engine.hpp"

#include "bintjekit/engine/play_ground.hpp"

namespace bnjkit {
    namespace engine {
        IEngine::IEngine() {
            m_play_ground = std::make_unique<PlayGround>();
        }

        IEngine::~IEngine() = default;

        void IEngine::initialise() {
            IModule::initialise();
            m_play_ground->size = {100, 100};
            m_play_ground->position = {0, 0};
        }

        void IEngine::update() {
            m_play_ground->update();
        }

        void IEngine::on_sfml_event(const sf::Event &event) {
        }

        void IEngine::configure() {
        }
    } // engine
} // bnjkit
