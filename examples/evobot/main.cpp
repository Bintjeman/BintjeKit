/*!
 * @author bintjeman
 * @date 26.06.25
 * @name main.cpp
 */
#include "application/application.hpp"
int main(int argc, const char** argv) {
    evo::app::Application application(argc, argv);
    application.init();
    application.configure();
    application.run();
    return 0;
}
