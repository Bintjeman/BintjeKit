/*!
 * @author bintjeman
 * @date 17.07.25
 * @name main.cpp
 */
#include <bintjekit/core.hpp>

#include "bintjekit/core/common.hpp"
#include "bintjekit/logger/logger.hpp"
int main() {
    std::shared_ptr<spdlog::logger> m_logger;
    m_logger = bnjkit::core::Logger::get_logger(bnjkit::literals::logger::CORE);
    bnjkit::core::Logger::get_logger(bnjkit::literals::logger::CORE);
    auto core = bnjkit::core::CoreBuilder()
            .build();
    core->initialise();
    core->configure();
    core->run();
    return 0;
}
