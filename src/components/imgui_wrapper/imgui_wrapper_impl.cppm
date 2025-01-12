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
export module bik.imgui_wrapper:impl;
import :interface;
import bik.window;
namespace bik::imguiwrapper {
    BaseImGuiWrapper::BaseImGuiWrapper() {
    }

    BaseImGuiWrapper::~BaseImGuiWrapper() {
    }

    void BaseImGuiWrapper::set_window(const std::shared_ptr<window::BaseWindow> &window) {
        window_ = window;
    }

    void BaseImGuiWrapper::initialize() {
        ImGui::SFML::Init(*window_);
        clock.restart();
    }

    void BaseImGuiWrapper::finalize() {
        ImGui::SFML::Shutdown();
    }

    void BaseImGuiWrapper::update() {
        ImGui::SFML::Update(*window_, clock.restart());
    }

    void BaseImGuiWrapper::render() {
        ImGui::SFML::Render(*window_);
    }
}
