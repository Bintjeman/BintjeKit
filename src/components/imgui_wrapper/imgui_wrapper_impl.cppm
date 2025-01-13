/*!
 * @file imgui_wrapper_impl.cppm
 * @author bintjeman
 * @date 12.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include "external/dear_imgui/imgui.h"
#include "external/dear_imgui/imgui-SFML.h"
#include "tools/logger/logger_define.hpp"
export module bik.imgui_wrapper:impl;
import :interface;
import bik.window;
import bik.logger;
namespace bik::imguiwrapper {
    BaseImGuiWrapper::BaseImGuiWrapper() {
        LOGGER->info("ImGuiWrapper::ImGuiWrapper()");
    }

    BaseImGuiWrapper::~BaseImGuiWrapper() {
        LOGGER->info("ImGuiWrapper::~ImGuiWrapper()");
    }

    void BaseImGuiWrapper::set_window(const std::shared_ptr<window::BaseWindow> &window) {
        LOGGER->debug("ImGuiWrapper::set_window()");
        window_ = window;
    }

    void BaseImGuiWrapper::initialize() {
        LOGGER->info("ImGuiWrapper::initialize()");
        ImGui::SFML::Init(*window_);
        clock.restart();
    }

    void BaseImGuiWrapper::finalize() {
        LOGGER->info("ImGuiWrapper::finalize()");
        LOGGER->flush();
        ImGui::SFML::Shutdown();

    }

    void BaseImGuiWrapper::update() {
        ImGui::SFML::Update(*window_, clock.restart());
    }

    void BaseImGuiWrapper::draw() {
    }

    void BaseImGuiWrapper::render() {
        ImGui::SFML::Render(*window_);
    }
}
