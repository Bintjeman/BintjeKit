/*!
 * @author bintjeman
 * @date 14.06.25
 * @name play_ground.cpp
 */

#include "bintjekit/engine/play_ground.hpp"

namespace bnjkit {
    namespace engine {
        PlayGround::PlayGround() = default;

        PlayGround::~PlayGround() = default;

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
