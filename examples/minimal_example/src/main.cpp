/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main.cpp
 * @example minimal_example
 * @brief Minimal example showing basic usage of core
*/
#include <iostream>
#include <bintjekit/core/core.hpp>
#include "bintjekit/core/core_builder.hpp"
int main() {
    std::cout << "Hello World!" << std::endl;
    auto core = bnjkit::core::CoreBuilder().build();
    core->run();
}
