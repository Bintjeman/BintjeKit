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

    namespace imguiwrapper {
        export class BaseImGuiWrapper;
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
        void set_factory(std::unique_ptr<factory::BaseFactory> factory);
        void configure();
        void initialize();
        void run();
        void on_close_window() override;
        // Getters
        [[nodiscard]] double renderer_effective_frequency() const override;
        [[nodiscard]] double playground_effective_frequency() const override;
        [[nodiscard]] double renderer_target_frequency() const override;
        [[nodiscard]] double playground_target_frequency() const override;

    private:
        void create_components();
        void finalize();

        bool run_ = false;

        config::Settings settings_;
        std::unique_ptr<factory::BaseFactory> factory_;
        std::shared_ptr<window::BaseWindow> window_ = nullptr;
        std::shared_ptr<ui::BaseUI> ui_ = nullptr;
        std::shared_ptr<playground::BasePlayGround> playground_ = nullptr;
        std::shared_ptr<renderer::BaseRenderer> renderer_ = nullptr;
        std::shared_ptr<imguiwrapper::BaseImGuiWrapper> imgui_wrapper_ = nullptr;

        time::Pulser playground_pulser_;
        time::Pulser ui_pulser_;
        time::Pulser renderer_pulser_;
    };
}
