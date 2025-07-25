/*!
 * @author bintjeman
 * @date 22.07.25
 * @name application.cpp
 */
#include "application.hpp"
#include <bintjekit/core.hpp>
#include <bintjekit/configuration/utils.hpp>
#include <bintjekit/configuration/settings.hpp>
#include "common.hpp"
#include "initializer.hpp"
#include "modules.hpp"

namespace evo::application {
    Application::Application() = default;
    Application::~Application() = default;
    void Application::initialisation(const int argc, char** argv) {
        initializer::Initializer::initialise(argc, argv);
        m_core = bnjkit::core::CoreBuilder()
                .set<window::MainWindow>()
                .set<imgui::ImGuiRenderer>()
                .set<engine::Engine>()
                .set<renderer::Renderer>()
                .set<event::EventManager>()
                .build();
        m_settings = std::make_shared<bnjkit::conf::Settings>();
        m_settings->load_from_json(bnjkit::conf::from_file(common::data.settings_path));
        m_settings->set_path(common::data.settings_path);
        initializer::Initializer::configure(* m_settings);
        m_core->set_settings(m_settings);
    }
    void Application::configure() const {
        m_core->configure();
    }
    void Application::run() const {
        m_core->run();
    }
    void Application::on_quit() const {
        initializer::Initializer::on_quit(* m_settings);
        m_settings->save_to_file();
    }
} // evo
