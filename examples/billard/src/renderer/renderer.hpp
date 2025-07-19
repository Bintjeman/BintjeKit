/*!
 * @author bintjeman
 * @date 19.07.25
 * @name renderer.hpp
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once
#include <bintjekit/renderer/default_renderer.hpp>

namespace bil {
    class Renderer : public bnjkit::renderer::DefaultRenderer {
    public:
        Renderer();
        ~Renderer() override;
        void initialise() override;
        void configure() override;
        [[nodiscard]] std::string name() const override;
    };
} // bil

#endif //RENDERER_HPP
