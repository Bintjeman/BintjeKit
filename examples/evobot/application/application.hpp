/*!
 * @author bintjeman
 * @date 26.06.25
 * @name application.hpp
 */

#ifndef  EVO_APPLICATION_HPP
#define  EVO_APPLICATION_HPP
#pragma once
#include <map>
#include <memory>
#include <vector>
#include <spdlog/fwd.h>
#include "defaults_options.hpp"
namespace bnjkit {
    namespace core {
        class Core;
    } // core
} // bnjkit
namespace evo {
    namespace app {

        class Application {
        public:
            Application(int argc = 0, const char** argv = nullptr);
            ~Application();
            void init();
            void configure();
            void run();

        private:
            static void parse_args(int argc, const char** argv);
            static void init_logger();
            void update_config();
            std::vector<opt::Option> args_options;
            std::unique_ptr<bnjkit::core::Core> m_core;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    } // app
} // evo

#endif // EVO_APPLICATION_HPP
