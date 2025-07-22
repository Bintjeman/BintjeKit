/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_system.hpp
 */

#ifndef  BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
#define  BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
#pragma once
#include <string>

namespace bnjkit::engine {
    class IEngine;
}

namespace bnjkit::ecs {
    /*!
     * Class interface et générique pour tout les systems
     *
     * Utilisée par plusieurs types de system (@ref bnjkit::renderer::IRenderSystem) typiquement dnas des gestionnaires de systems
     * par exemple @ref bnjkit::renderer::RenderSystemManager.
     *
     * @see bnjkit::Renderer
     * @see bnjkit::Engine
     */
    class ISystem {
    public:
        ISystem();
        virtual ~ISystem();
        virtual void initialize(engine::IEngine& engine);
        virtual void update(engine::IEngine& engine);
        virtual void cleanup(engine::IEngine& engine);
        [[nodiscard]] virtual std::string name() const;
    };
}

#endif // BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
