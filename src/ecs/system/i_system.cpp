/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_system.cpp
 */
#include "bintjekit/ecs/system/i_system.hpp"

namespace bnjkit::ecs {
    ISystem::ISystem() = default;
    ISystem::~ISystem() = default;
    void ISystem::initialize(engine::IEngine& engine[[maybe_unused]]) {}
    void ISystem::update(engine::IEngine& engine[[maybe_unused]]) {}
    void ISystem::cleanup(engine::IEngine& engine[[maybe_unused]]) {}
    std::string ISystem::name() const {
        return "ISystem";
    }
}
