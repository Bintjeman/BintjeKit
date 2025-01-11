/*!
 * @file factory.cppm
 * @author bintjeman
 * @date 11.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
export module min.factory;
export import bik.factory;
export import min.playground;
export import min.ui;
namespace min {
    export class Factory : public bik::factory::BaseFactory {
    public:
        void build_playground() override {
            components_["playground"] = std::make_unique<min::PlayGround>();
        }

        void build_ui() override {
            components_["ui"] = std::make_unique<min::UI>();
        }
    };
}