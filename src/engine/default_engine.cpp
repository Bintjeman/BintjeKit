/*!
 * @author bintjeman
 * @date 17.07.25
 * @name default_engine.cpp
 */

#include "bintjekit/engine/default_engine.hpp"

#include "bintjekit/engine/play_ground.hpp"

namespace bnjkit::engine {
    DefaultEngine::DefaultEngine() {
        m_logger->warn("DefaultEngine created");
    };
    DefaultEngine::~DefaultEngine() {
        m_logger->warn("DefaultEngine destroyed");
    }
    void DefaultEngine::configure() {
        m_logger->warn("DefaultEngine configuring");
        IEngine::configure();
        m_play_ground->position = {-500.f, -500.f};
        m_play_ground->size = {1000.f, 1000.f};
    }
    std::string DefaultEngine::name() const {
        return "DefaultEngine";
    };
}
