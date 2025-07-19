/*!
 * @author bintjeman
 * @date 18.07.25
 * @name main.cpp
 */
#include "users_types.hpp"
#include "bintjekit/core.hpp"
int main() {
    auto core = bnjkit::core::CoreBuilder()
    .set<utypes::Engine>()
    .set<utypes::EventManager>()
    .set<utypes::Window>()
    .set<utypes::ImGuiRenderer>()
    .build();
    core->run();
    return 0;
}
