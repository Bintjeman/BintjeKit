/*!
 * @author bintjeman
 * @date 19.06.25
 * @name toto.hpp
 */
#ifndef TOTO_TOTO_HPP
#define TOTO_TOTO_HPP
#pragma once
#include <vector>
#include <bintjekit/engine/i_engine.hpp>
#include "entity.hpp"

namespace toto {
    class TotoEngine : public bnjkit::engine::IEngine {
    public:

    private:
        std::vector<std::shared_ptr<Entity> > m_entities;
    };
} // toto
#endif // TOTO_TOTO_HPP
