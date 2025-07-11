/*!
 * @author bintjeman
 * @date 11.07.25
 * @name entity_manager.hpp
 */

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP
#pragma once
#include <bintjekit/entity/entity_manager.hpp>

namespace evo::entity {
    class  EvoEntityManager : public bnjkit::entity::EntityManager {
    public:
        EvoEntityManager();
        ~EvoEntityManager();
        void init();
    };
}
#endif //ENTITY_MANAGER_HPP
