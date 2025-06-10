/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main.cpp
 */
#include <iostream>

#include <bintjekit/window/main_window.hpp>
int main() {
    std::cout << "Hello World!" << std::endl;
    bnjkit::MainWindow main_window;
    main_window.open();
}
