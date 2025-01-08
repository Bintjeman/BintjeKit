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
namespace gol {
    export class Factory : public bik::factory::BaseFactory {
        protected:
        void build_playground() override {
            playground_ = std::make_shared<gol::GameOfLife>();
        }
        void build_ui() override {
            ui_ = std::make_shared<gol::UserInterface>();
        }
    };
}
