/*!
 * @author bintjeman
 * @date 26.06.25
 * @name entitymanager.hpp
 */

#ifndef BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#define BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
#pragma once
#include "bintjekit/entity/group.hpp"
namespace bnjkit {
    namespace entity {
        class EntityManager {
        public:
            EntityManager();
            ~EntityManager();
        protected:
            IGroup m_group;
        private:
        };
    } // entity
} // bnjkit

#endif // BINTJEKIT_ENTITY_ENTITYMANAGER_HPP
