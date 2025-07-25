/*!
 * @author bintjeman
 * @date 22.07.25
 * @name application.hpp
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once
#include <memory>

namespace bnjkit::conf {
    class Settings;
}

namespace bnjkit::core {
    class Core;
}

namespace evo::application {
    class Application {
    public:
        Application();
        ~Application();
        void initialisation(int argc, char** argv);
        void configure() const;
        void run() const;
        void on_quit() const;

    private:
        std::shared_ptr<bnjkit::conf::Settings> m_settings;
        std::unique_ptr<bnjkit::core::Core> m_core;
    };
} // evo

#endif //APPLICATION_HPP
