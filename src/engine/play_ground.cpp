/*!
 * @author bintjeman
 * @date 14.06.25
 * @name play_ground.cpp
 */

#include "bintjekit/engine/play_ground.hpp"
#include "bintjekit/utils/fmt_sfml/fmt_sfml.hpp"
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::engine {
    PlayGround::PlayGround() {
        m_logger = core::Logger::get_logger(literals::logger::ENGINE);
        m_logger->info("Constructor of PlayGround");
    }

    PlayGround::~PlayGround() {
        m_logger->info("Destructor of PlayGround");
    }

    void PlayGround::initialise() const {
        m_logger->trace("Initialising PlayGround");
    }

    void PlayGround::configure() const {
        m_logger->trace("Configuring PlayGround");
    }

    void PlayGround::update() {
        m_ticks_counter++;
    }

    long int PlayGround::ticks() const {
        return m_ticks_counter;
    }

    sf::Rect<float> PlayGround::bounds() const {
        return {{position}, {size}};
    }
}
