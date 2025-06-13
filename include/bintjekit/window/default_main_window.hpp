/*!
 * @author bintjeman
 * @date 11.06.25
 * @name default_main_window.hpp
 */

#ifndef DEFAULT_MAIN_WINDOW_HPP
#define DEFAULT_MAIN_WINDOW_HPP
#pragma once
#include "bintjekit/window/i_main_window.hpp"
namespace bnjkit::window {
    /**
     * A concrete implementation of the IMainWindow interface, providing the main
     * window functionalities. This class is responsible for initializing,
     * configuring, displaying, and managing SFML-based events for the main
     * application window.
     */
    class DefaultMainWindow : public IMainWindow{
public:
    DefaultMainWindow();
    ~DefaultMainWindow() override;
    void initialise() override;
    void configure() override;
    void show() override;
    void on_sfml_event(const sf::Event &event) override;
};
} // bnjkit::window
#endif //DEFAULT_MAIN_WINDOW_HPP
