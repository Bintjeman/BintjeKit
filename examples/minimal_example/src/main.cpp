/*!
 * @author bintjeman
 * @date 10.06.25
 * @name main.cpp
 * @example minimal_example
 * @brief Minimal example showing basic usage of core
*/
#include <iostream>
#include <bintjekit/core/core.hpp>
#include <bintjekit/core/core_builder.hpp>
#include <bintjekit/renderer/i_renderer.hpp>
#include <bintjekit/renderer/i_engine_renderer.hpp>
#include <bintjekit/engine/i_engine.hpp>
class MyEngine : public bnjkit::engine::IEngine {
public:
    void update() override{}
};
class MyEngineRenderer : public bnjkit::renderer::IEngineRenderer {};
class MyRenderer: public bnjkit::renderer::IRenderer {
public:
    void on_sfml_event(const sf::Event &event) override{}
};
int main() {
    std::cout << "Hello World!" << std::endl;
    auto core = bnjkit::core::CoreBuilder()
    .set<MyEngine>()
    .set<MyEngineRenderer>()
    .set<MyRenderer>()
    .build();
    core->run();
}
