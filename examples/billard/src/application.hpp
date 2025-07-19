/*!
 * @author bintjeman
 * @date 19.07.25
 * @name application.hpp
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>
namespace bnjkit::core {
    class Core;
}

namespace bil {
    class Application {
    public:
        Application();
        ~Application();
        void initialisation();
        void run();
        std::shared_ptr<spdlog::logger> logger();
    private:
        std::unique_ptr<bnjkit::core::Core> m_core;
        std::shared_ptr<spdlog::logger> m_logger;
    };
} // bil

#endif //APPLICATION_HPP
