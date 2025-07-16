/*!
 * @author bintjeman
 * @date 16.07.25
 * @name render_layer.hpp
 */

#ifndef BINTJEKIT_RENDERER_RENDER_LAYER_HPP
#define BINTJEKIT_RENDERER_RENDER_LAYER_HPP
#pragma once
namespace bnjkit::renderer {
    enum class RenderPriority {
        BACKGROUND = 0,
        WORLD = 100,
        ENTITIES = 200,
        EFFECTS = 300,
        DEBUG = 400,
        UI = 500
    };
    using RenderLayer = RenderPriority;
}
#endif //BINTJEKIT_RENDERER_RENDER_LAYER_HPP
