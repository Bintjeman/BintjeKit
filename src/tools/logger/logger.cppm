/*!
 * @file logger.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
export module bik.logger;
export import :interface;
export import :extension;
import :impl;
namespace bik {
    export using logger = utils::logger::Logger;
}
