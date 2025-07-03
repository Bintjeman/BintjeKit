/*!
 * @author bintjeman
 * @date 14.06.25
 * @name play_ground.cpp
 */

#include "bintjekit/engine/play_ground.hpp"
#include "fmt_sfml/fmt_sfml.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit {
    namespace engine {
        PlayGround::PlayGround() {
            m_logger = core::Logger::get_logger(core::module_names::ENGINE);
            m_logger->info("Constructor of PlayGround");
        }

        PlayGround::~PlayGround() {
            m_logger->info("Destructor of PlayGround");
        }

        void PlayGround::initialise() {
            m_logger->debug("Initialising PlayGround");
        }

        void PlayGround::configure() {
            m_logger->debug("Configuring PlayGround");
        }

        void PlayGround::update() {
            ticks_counter++;
        }

        long int PlayGround::ticks() const {
            return ticks_counter;
        }

        sf::Rect<float> PlayGround::bounds() const {
            return {{position}, {size}};
        }
    } // engine
} // bnjkit
