/*!
 * @author bintjeman
 * @date 15.06.25
 * @name bnjkit_imgui.cpp
 */
#include "bintjekit/renderer/i_bnjkit_imgui.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
#include "bintjekit/renderer/i_renderer.hpp"

namespace bnjkit {
    namespace renderer {
        IImGuiRenderer::ImGuiContext::ImGuiContext(sf::RenderWindow* window) {
            if (!ImGui::SFML::Init(* window)) {
                throw std::runtime_error("IImGuiRenderer: Failed to initialise ImGui");
            }
        }

        IImGuiRenderer::ImGuiContext::~ImGuiContext() {
            ImGui::SFML::Shutdown();
        }

        IImGuiRenderer::IImGuiRenderer() {
            m_logger = core::Logger::get_logger(core::module_names::RENDERER);
            m_logger->info("Constructor of IImGuiRenderer");
        }

        IImGuiRenderer::~IImGuiRenderer() {
            m_logger->info("Destructor of IImGuiRenderer");
        }

        void IImGuiRenderer::set_window(sf::RenderWindow* window) {
            m_logger->debug("IImGuiRenderer: Setting window");
            m_window = window;
        }
        void IImGuiRenderer::set_engine(engine::IEngine* engine) {
            m_logger->debug("IImGuiRenderer: Setting engine");
            m_engine = engine;
        }
        void IImGuiRenderer::set_core(core::Core* core) {
            m_logger->debug("IImGuiRenderer: Setting core");
            m_core = core;
        }
        void IImGuiRenderer::set_core_event_handler(event::ICoreEventHandler* core_event_handler) {
            m_logger->debug("IImGuiRenderer: Setting core event handler");
            m_core_event_handler = core_event_handler;
        }
        void IImGuiRenderer::set_renderer(IRenderer* renderer) {
            m_logger->debug("IImGuiRenderer: Setting renderer");
            m_renderer = renderer;
        }

        void IImGuiRenderer::update() {
            static sf::Clock clock;
            ImGui::SFML::Update(* m_window, clock.restart());
        }

        void IImGuiRenderer::init() {
            m_logger->debug("IImGuiRenderer: Initialising ImGui");
            m_context = std::make_unique<ImGuiContext>(m_window);
        }

        void IImGuiRenderer::process_events(sf::Event& event) {
            ImGui::SFML::ProcessEvent(* m_window, event);
        }

        void IImGuiRenderer::draw() {
        }

        void IImGuiRenderer::render() {
            ImGui::SFML::Render(* m_window);
        }

        void IImGuiRenderer::shutdown() {
            ImGui::SFML::Shutdown();
        }
        std::string IImGuiRenderer::name() const {
            return "IImGuiRenderer";
        }
    } // renderer
} // bnjkit
