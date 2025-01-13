/*!
 * @file imgui.cppm
 * @author bintjeman
 * @date 13.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include "external/dear_imgui/imgui.h"
export module gol.imgui;
import bik.imgui_wrapper;
namespace gol::imgui {
    export class Imgui : public bik::imguiwrapper::BaseImGuiWrapper {
        public:
        void draw() override {
        }
    };
}
