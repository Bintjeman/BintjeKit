/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.cpp
 */

#include "bintjekit/engine/i_engine.hpp"

#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"
#include "bintjekit/engine/play_ground.hpp"

namespace bnjkit {
    namespace engine {
        IEngine::IEngine() {
            m_logger = core::Logger::get_logger(core::module_names::ENGINE);
            m_logger->info("Constructor of IEngine");
            m_play_ground = std::make_unique<PlayGround>();
        }

        IEngine::~IEngine() {
            m_logger->info("Destructor of IEngine");
        }

        void IEngine::initialise() {
            m_logger->info("Initialising IEngine");
            m_play_ground->size = {100, 100};
            m_play_ground->position = {0, 0};
        }
        void IEngine::configure() {
            m_logger->info("Configuring IEngine");
        }
        void IEngine::update() {
            m_play_ground->update();
        }

        void IEngine::on_sfml_event(const sf::Event &event) {
        }

        PlayGround &IEngine::play_ground() const { return *m_play_ground; }


    } // engine
} // bnjkit
