/*!
 * @author bintjeman
 * @date 22.07.25
 * @name main.cpp
 */
#include "application.hpp"
int main(int argc, char** argv) {
    evo::application::Application application;
    application.initialisation(argc, argv);
    application.configure();
    application.run();
    application.on_quit();
}
