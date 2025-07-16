/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_system.cpp
 */

#include "bintjekit/ECS/system/i_system.hpp"

namespace bnjkit::engine {
    ISystem::ISystem(const std::string& name) : m_name(name){};
    ISystem::~ISystem() = default;
    void ISystem::initialize(IWorld& world[[maybe_unused]]) {}
    void ISystem::update(IWorld& world[[maybe_unused]]) {}
    void ISystem::cleanup(IWorld& world[[maybe_unused]]) {}
    std::string ISystem::name() const {
        return m_name;
    }
}
