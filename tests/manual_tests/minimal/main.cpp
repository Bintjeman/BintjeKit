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
#include <memory>
import core;
import factory;
import factory_child;
import logger;
int main() {
    bik::utils::logger::Logger::init();
    auto& logger = bik::utils::logger::Logger::getLogger();
    logger->info("TEst");
    std::unique_ptr<bik::factory::Factory> factory = std::make_unique<bik::factory::Factory>();
    bik::core::Core core(std::move(factory));
    core.hw();
    bik::core::Core core_2(std::make_unique<min::Child>());
    core_2.hw();
    bik::core::Core core_3;
    core_3.hw();
    return 0;
}
