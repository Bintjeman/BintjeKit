/*!
 * @author bintjeman
 * @date 12.06.25
 * @name i_renderer.hpp
 */

#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP
#pragma once
namespace bnjkit {
    namespace renderer {
        class IRenderer {
        public:
            virtual ~IRenderer() = default;
            virtual void initialise() = 0;
            virtual void configure() = 0;
            virtual void render() = 0;

            virtual void renderGUI() = 0;
        protected:
        };
    } // renderer
} // bnjkit
#endif //I_RENDERER_HPP
