/*!
 * @file has_settings.cppm
 * @author bintjeman
 * @date 17.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module bik.settings:has_settings;
import :interface;
namespace bik::settings {
    export class HasSettings {
    public:
        inline virtual ~HasSettings() = default;

        virtual void configure(const Child& settings) {
            settings_ = settings;
        }

        virtual void initialize() {
        }

    protected:
        Child settings_{};
    };
}
