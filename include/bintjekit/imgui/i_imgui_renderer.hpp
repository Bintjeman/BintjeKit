/*!
 * @author bintjeman
 * @date 15.06.25
 * @name imgui.hpp
 */
#ifndef BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
#define BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
#pragma once
#include <memory>
#include "bintjekit/core/i_module.hpp"
namespace sf {
    class RenderWindow;
    class Event;
}
namespace bnjkit::core {
    class ModuleSet;
}
namespace bnjkit::renderer {
    class IRenderer;
}
namespace bnjkit::imgui {
    class IImGuiRenderer : public core::IModule {
        class ImGuiContext {
        public:
            explicit ImGuiContext(sf::RenderWindow* window);
            ~ImGuiContext();
        };

    public:
        IImGuiRenderer();
        ~IImGuiRenderer() override;
        void initialise() override;
        void set_modules(core::ModuleSet* modules);
        virtual void update();
        virtual void process_events(const sf::Event& event);
        virtual void draw();
        void render() const;
        static void shutdown();
        [[nodiscard]] std::string name() const override;
    protected:
        core::ModuleSet* m_modules;
    private:
        std::unique_ptr<ImGuiContext> m_context;

    public:
        IImGuiRenderer(const IImGuiRenderer&) = delete;
        IImGuiRenderer& operator=(const IImGuiRenderer&) = delete;
    };
}
#endif // BNJKIT_RENDERER_BNJKIT_IMGUI_HPP
