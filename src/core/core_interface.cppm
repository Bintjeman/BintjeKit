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
// import bik.window;
// import bik.playground;
import bik.common;
// import bik.playground;
// import bik.factory;
import bik.time;
namespace bik {
    namespace window {
        export class BaseWindow;
    }

    namespace playground {
        export class BasePlayGround;
    }

    namespace renderer {
        export class BaseRenderer;
    }

    namespace ui {
        export class BaseUI;
    }

    namespace factory {
        export class BaseFactory;
    }
}

namespace bik::core {
    export class Core : public common::BaseIActionReceiver, public common::BaseCoreInfoProvider {
    public:
        Core();
        explicit Core(std::unique_ptr<factory::BaseFactory> factory);
        ~Core();
        //
        void configure();
        void initialize();
        void run();
        void finalize();
        void on_close_window() override;
        // Getters
        double renderer_frequency() const override;
        double playground_frequency() const override;
    private:
        void create_components();

        config::Settings settings_;
        std::unique_ptr<factory::BaseFactory> factory_;
        std::unique_ptr<window::BaseWindow> window_ = nullptr;
        std::unique_ptr<ui::BaseUI> ui_ = nullptr;
        std::unique_ptr<playground::BasePlayGround> playground_ = nullptr;
        std::unique_ptr<renderer::BaseRenderer> renderer_ = nullptr;

        time::Pulser playground_pulser_;
        time::Pulser ui_pulser_;
        time::Pulser renderer_pulser_;
    };
}
