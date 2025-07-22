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
        m_logger = logger::Logger::get_logger(literals::logger::ENGINE);
        m_logger->info("Constructor of PlayGround");
    }
    PlayGround::PlayGround(const sf::Rect<float>& bounds) {
        set_bounds(bounds);
    }
    PlayGround::PlayGround(const sf::Vector2f& position, const sf::Vector2f& size) {
        set_bounds(position, size);
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
    void PlayGround::set_bounds(const sf::Rect<float>& bounds) {
        m_bounds = bounds;
    }
    void PlayGround::set_bounds(const sf::Vector2f& position, const sf::Vector2f& size) {
        m_bounds.position = position;
        m_bounds.size = size;
    }
    void PlayGround::set_position(const sf::Vector2f& position) {
        m_bounds.position = position;
    }
    void PlayGround::set_size(const sf::Vector2f& size) {
        m_bounds.size = size;
    }
    sf::Rect<float> PlayGround::bounds() const {
        return m_bounds;
    }
    sf::Vector2f PlayGround::size() const {
        return m_bounds.size;
    }
    sf::Vector2f PlayGround::position() const {
        return m_bounds.position;
    }
}
