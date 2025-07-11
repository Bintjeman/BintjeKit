/*!
 * @author bintjeman
 * @date 26.06.25
 * @name application.hpp
 */

#ifndef  EVO_APPLICATION_HPP
#define  EVO_APPLICATION_HPP
#pragma once
// #include <map>
#include <memory>
// #include <vector>
#include <spdlog/fwd.h>
#include "defaults_options.hpp"
namespace bnjkit::core {
    class Core;
}

namespace evo::app {

    class Application {
    public:
        explicit Application(int argc = 0, const char** argv = nullptr);
        ~Application();
        void init();
        void configure();
        void run();

    private:
        static void parse_args(int argc, const char** argv);
        static void init_logger();
        void update_config();
        std::vector<opt::Option> m_args_options;
        std::unique_ptr<bnjkit::core::Core> m_core;
        std::shared_ptr<spdlog::logger> m_logger;
        const char** m_argv;
    };
}

#endif // EVO_APPLICATION_HPP
