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

import core;
import factory;
import logger;
int main() {
    bik::core::Core core;
    core.hw();
    core.configure();
    core.initialize();
    core.run();
    core.finalize();
    return 0;
}
