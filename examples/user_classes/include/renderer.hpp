/*!
 * @author bintjeman
 * @date 13.06.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "bintjekit/renderer/i_renderer.hpp"

namespace usr {
    class Renderer : public bnjkit::renderer::IRenderer {
    public:
        Renderer();
        ~Renderer() override;
        void initialise() override;
        void configure() override;
        void render() override;
        void renderGUI() override;
    };
} // usr

#endif //RENDERER_HPP
