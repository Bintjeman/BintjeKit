/*!
 * @author bintjeman
 * @date 26.06.25
 * @name main.cpp
 */
#include "bintjekit/core.hpp"
int main() {
    auto core = bnjkit::core::CoreBuilder().build();
    core->configure("life.json");
    core->run();
    core->save_settings();
    return 0;
}
