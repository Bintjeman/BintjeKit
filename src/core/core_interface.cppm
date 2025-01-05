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
import window;
export import factory;
namespace bik::core {
    export class Core {
    public:
        explicit Core(std::unique_ptr<factory::Factory> factory);
        ~Core();

        void configure();
        void initialize();
        void run();
        void finalize();

    private:
        void create_components();

        std::unique_ptr<factory::Factory> factory_;
        std::shared_ptr<window::Window> window_;

        // Debug et test
    public:
        [[deprecated("Seulement pour des tests")]]
        Core();

        [[deprecated("Seulement pour des tests")]]
        void hw();
    };
}
