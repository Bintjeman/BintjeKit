/*!
 * @author bintjeman
 * @date 17.07.25
 * @name main.cpp
 */
#include <bintjekit/core.hpp>

#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
int main() {
    bnjkit::core::Logger::get_logger(bnjkit::literals::logger::CORE);
    auto core = bnjkit::core::CoreBuilder()
            .build();
    core->run();
    return 0;
}
