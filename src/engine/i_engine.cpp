/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.cpp
 */

#include "bintjekit/engine/i_engine.hpp"

#include "bintjekit/core/common.hpp"
#include "bintjekit/core/core.hpp"
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

        PlayGround &IEngine::play_ground() const { return *m_play_ground; }

        IEngine::State IEngine::state() const {
            return m_state;
        }

        std::string IEngine::state_to_string(State state) {
            switch (state) {
                case EMPTY:
                    return "EMPTY";
                case FINISH:
                    return "FINNISH";
                case READY:
                    return "READY";
                default:
                    return "UNKNOWN";
            }
        }
        std::string IEngine::name() const {
            return "IEngine";
        }
        void IEngine::on_sfml_event(const sf::Event& event[[maybe_unused]]) {
        }
    } // engine
} // bnjkit
