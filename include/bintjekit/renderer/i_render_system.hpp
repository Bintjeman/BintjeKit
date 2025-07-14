/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_render_system.hpp
 */

#ifndef I_RENDER_SYSTEM_HPP
#define I_RENDER_SYSTEM_HPP
#pragma once
#include <memory>
#include <string>
#include <spdlog/fwd.h>

namespace sf {
    class View;
    class RenderTarget;
}

namespace bnjkit::renderer {
    class IRenderSystem {
    public:
        IRenderSystem();
        virtual ~IRenderSystem();

        // Méthodes principales
        virtual void render(sf::RenderTarget& target) const;
        virtual void update();

        // Configuration
        virtual void configure();
        [[nodiscard]] virtual std::string name() const;
    protected:
        std::shared_ptr<spdlog::logger> m_logger;
    };
}

#endif //I_RENDER_SYSTEM_HPP
