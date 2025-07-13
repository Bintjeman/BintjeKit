/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_engine.cpp
 */

#include "bintjekit/engine/i_engine.hpp"

#include "bintjekit/core/common.hpp"
#include "bintjekit/core/core.hpp"
#include "bintjekit/logger/logger.hpp"

namespace bnjkit::engine {
    IEngine::IEngine() {
        m_logger = core::Logger::get_logger(core::module_names::ENGINE);
        m_logger->info("Constructor of IEngine");
    }
    IEngine::~IEngine() {
        m_logger->info("Destructor of IEngine");
    }
    void IEngine::initialise() {
        m_logger->debug("Initialising IEngine");
    }

    void IEngine::configure() {
        m_logger->debug("Configuring IEngine");
    }

    void IEngine::update() {
    }
    IEngine::State IEngine::state() const {
        return m_state;
    }

    std::string IEngine::state_to_string(const State state) {
        switch (state) {
            case State::EMPTY:
                return "EMPTY";
            case State::FINISH:
                return "FINNISH";
            case State::READY:
                return "READY";
            default:
                return "UNKNOWN";
        }
    }
    void IEngine::on_sfml_event(const sf::Event& event[[maybe_unused]]) {
    }
    std::string IEngine::name() const {
        return "IEngine";
    }
}
