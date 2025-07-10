/*!
 * @author bintjeman
 * @date 10.07.25
 * @name health.hpp
 */

#ifndef HEALTH_HPP
#define HEALTH_HPP
#pragma once
#include <algorithm>

#include "bintjekit/entity/components/component.hpp"

namespace evo {
    namespace entity {
        class Health final : public bnjkit::entity::IComponent {
        public:
            explicit Health(float initial = 100.0f) : m_current(initial), m_max(initial) {}

            float current() const { return m_current; }
            float max() const { return m_max; }

            void damage(float amount) {
                m_current = std::max(0.0f, m_current - amount);
            }

            void heal(float amount) {
                m_current = std::min(m_max, m_current + amount);
            }

        private:
            float m_current;
            float m_max;
        };
    } // entity
} // evo

#endif //HEALTH_HPP
