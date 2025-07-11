/*!
 * @author bintjeman
 * @date 10.07.25
 * @name component_register.cpp
 */

#include "../../../include/bintjekit/entity/components/component_register.hpp"

namespace bnjkit::entity {
    IComponentRegistry::~IComponentRegistry() {}
    void IComponentRegistry::remove(EntityId entity_id [[maybe_unused]]) {}
    void IComponentRegistry::clear() {}
}
