/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_engine.cpp
 */

#include "bintjekit/engine/default_engine.hpp"

namespace bnjkit::engine {
    DefaultEngine::DefaultEngine() {
        m_logger->warn("DefaultEngine created");
    };
    DefaultEngine::~DefaultEngine() {
        m_logger->warn("DefaultEngine destroyed");
    };
}
