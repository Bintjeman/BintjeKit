/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.hpp
 */
#ifndef CORE_HPP
#define CORE_HPP
#pragma once
#include <memory>
#include "bintjekit/window/i_main_window.hpp"
namespace bnjkit::window {
    class  IMainWindow;
}
namespace bnjkit::core {

    class Core {
    public:
        Core();
        ~Core();
        void set_modules(std::unique_ptr<window::IMainWindow> window);
        void run();

    private:
        std::unique_ptr<window::IMainWindow> m_main_window;

    public:
        Core(const Core &) = delete;
        Core &operator=(const Core &) = delete;
    };
} // bnjkit::core
#endif //CORE_HPP
