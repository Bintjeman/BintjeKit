/*!
 * @author bintjeman
 * @date 18.07.25
 * @name engine.hpp
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP
#pragma once
#include <bintjekit/engine/default_engine.hpp>
namespace utypes {

class Engine : public bnjkit::engine::DefaultEngine{
public:
    Engine();
    ~Engine();
};

} // utypes

#endif //ENGINE_HPP
