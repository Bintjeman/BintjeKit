/*!
 * @author bintjeman
 * @date 15.06.25
 * @name bnjkit_imgui.cpp
 */
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "bintjekit/core/common.hpp"
#include "bintjekit/core/logger.hpp"

namespace bnjkit {
    namespace renderer {
        IImGuiRenderer::IImGuiRenderer() {
            m_logger = core::Logger::get_logger(core::module_names::RENDERER);
            m_logger->info("Constructor of IImGuiRenderer");
        }

        IImGuiRenderer::~IImGuiRenderer() {
            m_logger->info("Destructor of IImGuiRenderer");
        }

        void IImGuiRenderer::set_window(sf::RenderWindow *window) {
            m_logger->info("Setting window");
            m_window = window;
        }

        void IImGuiRenderer::update() {
            static sf::Clock clock;
            ImGui::SFML::Update(*m_window, clock.restart());
        }

        void IImGuiRenderer::init() {
            m_logger->info("Initialising ImGui");
            if (!ImGui::SFML::Init(*m_window)) {
                m_logger->error("Failed to initialise ImGui");
                throw std::runtime_error("Failed to initialise ImGui");
            }
        }

        void IImGuiRenderer::process_events(sf::Event &event) {
            ImGui::SFML::ProcessEvent(*m_window, event);
        }

        void IImGuiRenderer::draw() {
        }

        void IImGuiRenderer::render() {
            ImGui::SFML::Render(*m_window);
        }

        void IImGuiRenderer::shutdown() {
            ImGui::SFML::Shutdown();
        }
    } // renderer
} // bnjkit
