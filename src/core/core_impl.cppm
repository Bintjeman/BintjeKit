/*!
 * @file core_impl.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <iostream>
export module core:impl;
import :interface;
namespace bik {
    void Core::hw() {
        std::cout << "Je suis core de bintjeKit !" << std::endl;
    }
}
