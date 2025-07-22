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
namespace bnjkit::conf {
    class Node;
}
namespace bil {
    class Application {
    public:
        Application();
        ~Application();
        void initialisation();
        void configuration();
        void run();
        std::shared_ptr<spdlog::logger> logger();
    private:
        void update_setting();
        void init_logger(bnjkit::conf::Node& node);
        std::unique_ptr<bnjkit::core::Core> m_core;
        std::shared_ptr<spdlog::logger> m_logger;
    };
} // bil

#endif //APPLICATION_HPP
