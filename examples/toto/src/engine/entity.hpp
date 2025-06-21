/*!
 * @author bintjeman
 * @date 20.06.25
 * @name entity.hpp
 */

#ifndef TOTO_ENTITY_HPP
#define TOTO_ENTITY_HPP
#pragma once
#include "entity/components.hpp"

namespace toto {
    class Entity {
    public:
        Entity() = default;

    protected:
        D2 m_d2;

    private:
    };
} // toto

#endif // TOTO_ENTITY_HPP
