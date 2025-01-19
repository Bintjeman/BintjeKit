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
import bik.playground;
import bik.common;
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

    void BaseImGuiWrapper::
    set_core_info_provider(common::BaseCoreInfoProvider *core_info_provider) {
        core_info_provider_ = core_info_provider;
    }

    void BaseImGuiWrapper::set_playground(
        const std::shared_ptr<playground::BasePlayGround> &playground) {
        playground_ = playground;
    }

    void BaseImGuiWrapper::initialize() {
        LOGGER->info("ImGuiWrapper::setup_window()");
        if (ImGui::SFML::Init(*window_)) {
            LOGGER->info("ImGuiWrapper::setup_window() - done");
        } else {
            LOGGER->error("ImGuiWrapper::setup_window() - failed");
        }
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
