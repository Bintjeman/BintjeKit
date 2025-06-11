/*!
 * @author bintjeman
 * @date 11.06.25
 * @name main.cpp
 */
#include <memory>
#include <bintjekit/core/core.hpp>
#include "bintjekit/core/core_builder.hpp"
#include "main_window.hpp"

int main() {
    auto core = bnjkit::core::CoreBuilder()
            .set_window_module(std::make_unique<usr::MainWindow>()).build();
    return 0;
}
