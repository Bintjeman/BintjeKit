/*!
 * @author bintjeman
 * @date 15.06.25
 * @name bnjkit_imgui.cpp
 */
#include "bintjekit/renderer/i_imgui_renderer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "bintjekit/logger.hpp"
#include "bintjekit/core/module_set.hpp"
#include "bintjekit/window/i_main_window.hpp"
namespace bnjkit::renderer {
    IImGuiRenderer::ImGuiContext::ImGuiContext(sf::RenderWindow* window) {
        if (!ImGui::SFML::Init(* window)) {
            throw std::runtime_error("IImGuiRenderer: Failed to initialise ImGui");
        }
    }
    IImGuiRenderer::ImGuiContext::~ImGuiContext() {
        ImGui::SFML::Shutdown();
    }
    IImGuiRenderer::IImGuiRenderer(): m_modules(nullptr) {
        m_logger = core::Logger::get_logger(literals::logger::RENDERER);
        m_logger->info("Constructor of IImGuiRenderer");
    }
    IImGuiRenderer::~IImGuiRenderer() {
        m_logger->info("Destructor of IImGuiRenderer");
    }
    void IImGuiRenderer::initialise() {
        m_logger->trace("IImGuiRenderer: Initialising ImGui");
        IModule::initialise();
        static auto& window = dynamic_cast<sf::RenderWindow&>(m_modules->window());
        m_context = std::make_unique<ImGuiContext>(& window);
    }
    void IImGuiRenderer::update() {
        static sf::Clock clock;
        if (!m_modules->check_modules(false)) {
            m_logger->error("IImGuiRenderer: Modules not initialized");
        }
        static auto& window = dynamic_cast<sf::RenderWindow&>(m_modules->window());
        ImGui::SFML::Update(window, clock.restart());
    }
    void IImGuiRenderer::set_modules(core::ModuleSet* modules) {
        m_logger->trace("IImGuiRenderer: Setting modules");
        m_modules = modules;
    }
    void IImGuiRenderer::process_events(const sf::Event& event) {
        static auto& window = dynamic_cast<sf::RenderWindow&>(m_modules->window());
        ImGui::SFML::ProcessEvent(window, event);
    }
    void IImGuiRenderer::draw() {}
    void IImGuiRenderer::render() const {
        static auto& window = dynamic_cast<sf::RenderWindow&>(m_modules->window());
        ImGui::SFML::Render(window);
    }
    void IImGuiRenderer::shutdown() {
        ImGui::SFML::Shutdown();
    }
    std::string IImGuiRenderer::name() const {
        return "IImGuiRenderer";
    }
}
