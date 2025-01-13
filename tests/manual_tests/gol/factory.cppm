/*!
 * @file factory.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
export module gol.factory;
export import bik.factory;
import bik.playground;
import bik.ui;
import bik.window;
import gol;
import gol.user_interface;
import gol.renderer;
import gol.imgui;
namespace gol {
    export class Factory : public bik::factory::BaseFactory {
    protected:
        void build_playground() override {
            playground_ = std::make_shared<GameOfLife>();
        }

        void build_imgui_wrapper() override {
            imgui_wrapper_ = std::make_shared<imgui::Imgui>();
        }

        void build_ui() override {
            ui_ = std::make_shared<UserInterface>();
        }

        void build_renderer() override {
            renderer_ = std::make_shared<Renderer>();
        }
    };
}
