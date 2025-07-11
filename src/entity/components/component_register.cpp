/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_register.cpp
 */

#include "bintjekit/entity/components/component_register.hpp"

namespace bnjkit::entity {
    IComponentRegistry::~IComponentRegistry() =default;
    void IComponentRegistry::remove(EntityId entity_id [[maybe_unused]]) {}
    void IComponentRegistry::clear() {}
}
