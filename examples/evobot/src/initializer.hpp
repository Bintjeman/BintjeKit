/*!
 * @author bintjeman
 * @date 22.07.25
 * @name initialisation.hpp
 */

#ifndef INITIALISATION_HPP
#define INITIALISATION_HPP
#pragma once
namespace bnjkit::conf {
    class Settings;
}
namespace evo::initializer {
    class Initializer {
    public:
        static int initialise(int argc, char** argv);
        static void configure(bnjkit::conf::Settings& settings);
        static void on_quit(bnjkit::conf::Settings& settings);
    };
}
#endif