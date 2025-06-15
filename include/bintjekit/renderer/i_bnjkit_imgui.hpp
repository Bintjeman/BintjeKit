/*!
 * @author bintjeman
 * @date 15.06.25
 * @name imgui.hpp
 */
#ifndef BNJKIT_IMGUI_HPP
#define BNJKIT_IMGUI_HPP
#pragma once
#include <memory>

#include "spdlog/fwd.h"

namespace sf {
    class Event;
    class RenderWindow;
}
namespace bnjkit {
    namespace renderer {
        class IImGuiRenderer {
        public:
            IImGuiRenderer();
            virtual ~IImGuiRenderer();
            void set_window(sf::RenderWindow *window);
            void update();
            void init();
            void process_events(sf::Event& event);
            void render();
            static void shutdown();
        protected:
            std::shared_ptr<spdlog::logger> m_logger;
        private:
            sf::RenderWindow *m_window = nullptr;
        };
    } // renderer
} // bnjkit
#endif // BNJKIT_IMGUI_HPP
