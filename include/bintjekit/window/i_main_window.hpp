/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main_window.hpp
 */
#ifndef I_MAIN_WINDOW_HPP
#define I_MAIN_WINDOW_HPP
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "bintjekit/core/i_module.hpp"
#include "bintjekit/event_manager/i_event_listener.hpp"

namespace bnjkit::window {
    /**
     * @class IMainWindow
     * @brief Abstract interface for the main window of the application.
     *
     * This class combines functionality from multiple interfaces, serving
     * as a core module, a renderable window, and an event listener.
     * It provides a foundational level of abstraction for creating,
     * displaying, and managing the main graphical window of the application.
     *
     * Inherits from:
     * - core::IModule: Provides the module interface for system integration.
     * - sf::RenderWindow: Allows for rendering operations and SFML-specific
     *   window handling.
     * - event::IEventListener: Enables the window to handle and respond
     *   to system or user-generated events.
     *
     * Derived classes must implement the pure virtual function `show()`
     * to define specific behavior for displaying the window.
     */
    class IMainWindow : public core::IModule, public sf::RenderWindow, public event::IEventListener {

    public:
        IMainWindow();
        ~IMainWindow() override;
        /**
         * @brief Displays the main application window.
         *
         * This pure virtual method is responsible for making the main window
         * visible and initiating its rendering lifecycle. Concrete implementations
         * of this method must define the logic for displaying the window and
         * preparing it for user interaction.
         *
         * This method is invoked as part of the application's core execution flow
         * and should ensure all necessary setup for the window's operation is completed.
         *
         * Derived classes must implement this function to provide the specific behavior
         * required to render and manage the graphical interface.
         */
        virtual void show() = 0;
        /**
         * @brief Handles an SFML event.
         *
         * This method processes incoming SFML events and performs the necessary
         * actions based on the type of the event. It manages events like closing
         * the window or handling specific keypress inputs, providing a responsive
         * behavior to user interactions.
         *
         * @param event The SFML event to handle, passed as a constant reference.
         */
        void on_sfml_event(const sf::Event &event) override;

    private:
    };
} // bnjkit::window
#endif // I_MAIN_WINDOW_HPP
