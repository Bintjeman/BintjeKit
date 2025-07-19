/*!
 * @author bintjeman
 * @date 18.07.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once
#include <bintjekit/renderer/default_renderer.hpp>
namespace utypes {

class Renderer : public bnjkit::renderer::DefaultRenderer{
public:
    Renderer();
    ~Renderer();
};

} // utypes

#endif //RENDERER_HPP
