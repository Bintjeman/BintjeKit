/*!
 * @author bintjeman
 * @date 04.07.25
 * @name d2.cpp
 */

#include "d2.hpp"

namespace evo {
    namespace engine {
        D2::Bounds D2::bounds() const {
            return {
                {position.x - radius, position.y - radius},
                {position.x + radius, position.y + radius}
            };
        }
        void Movable::update() {
            position += velocity;
        }
    } // engine
} // evo
