/*!
 * @file main.cpp
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
#include <iostream>
#include <memory>
import core;
import factory;
import factory_child;
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::unique_ptr<bik::factory::Factory> factory = std::make_unique<bik::factory::Factory>();
    bik::core::Core core(std::move(factory));
    core.hw();
    bik::core::Core core_2(std::make_unique<min::Child>());
    core_2.hw();
    bik::core::Core core_3;
    core_3.hw();
    return 0;
}
