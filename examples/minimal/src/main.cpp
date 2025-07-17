/*!
 * @author bintjeman
 * @date 17.07.25
 * @name main.cpp
 */
#include <bintjekit/core.hpp>
int main(){
    auto core = bnjkit::core::CoreBuilder().build();
    core->run();
    return 0;
}