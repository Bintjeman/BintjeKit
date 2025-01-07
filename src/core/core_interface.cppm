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
export module core:interface;
import settings;
import window;
export import factory;
namespace bik::core {
    export class Core {
    public:
        Core();
        explicit Core(std::unique_ptr<factory::Factory> factory);
        ~Core();

        void configure(config::Child settings);
        void configure();
        void initialize();
        void run();
        void finalize();

    private:
        void create_components();
        void configure_inner();

        config::Settings settings_;
        std::unique_ptr<factory::Factory> factory_;
        std::shared_ptr<window::Window> window_ = nullptr;

    };
}
