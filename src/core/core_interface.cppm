/*!
 * @file core_interface.cppm
 * @author bintjeman
 * @date 05.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <memory>
export module bik.core:interface;
import bik.settings;
import bik.window;
import bik.common;
import bik.factory;
namespace bik {
    namespace ui {
        class BaseUI;
    }
}
namespace bik::core {
    export class Core : public common::BaseIActionReceiver{
    public:
        Core();
        explicit Core(std::unique_ptr<factory::BaseFactory> factory);
        ~Core();

        void configure();
        void initialize();
        void run();
        void finalize();

        void on_close_window() override;

    private:
        void create_components();
        void configure_inner();

        config::Settings settings_;
        std::unique_ptr<factory::BaseFactory> factory_;
        std::shared_ptr<window::BaseWindow> window_ = nullptr;
        std::shared_ptr<ui::BaseUI> ui_ = nullptr;
    };
}
