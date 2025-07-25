/*!
 * @author bintjeman
 * @date 23.07.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once
#include <bintjekit/renderer/i_renderer.hpp>

namespace evo::renderer {
    class Renderer final : public bnjkit::renderer::IRenderer {
        public:
        Renderer();
        ~Renderer() override;
        void configure() override;
        void on_quit() override;
        [[nodiscard]] std::string name() const override;
    };
}
#endif
