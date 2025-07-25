/*!
 * @author bintjeman
 * @date 16.07.25
 * @name modules.hpp
 *
 * @defgroup required_modules Modules Requis
 * @brief Liste des modules requis pour le fonctionnement du core
 * @{
 *     - bnjkit::window::IMainWindow
 *     - bnjkit::event::IEventManager
 *     - bnjkit::engine::IEngine
 *     - bnjkit::renderer::IRenderer
 *     - bnjkit::imgui::IImGuiRenderer
 * @}
 */
#ifndef BINTJEKIT_CORE_MODULES_HPP
#define BINTJEKIT_CORE_MODULES_HPP
#pragma once
#include "bintjekit/window/i_main_window.hpp"
#include "bintjekit/event_manager/i_event_manager.hpp"
#include "bintjekit/engine/i_engine.hpp"
#include "bintjekit/renderer/i_renderer.hpp"
#include "../imgui/i_imgui_renderer.hpp"
#endif // BINTJEKIT_CORE_MODULES_HPP
