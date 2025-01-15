/*!
 * @file core_info_profider.cppm
 * @author bintjeman
 * @date 09.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module bik.common:core_info_provider;
namespace bik::common {
    export class BaseCoreInfoProvider {
    public:
        virtual ~BaseCoreInfoProvider() = default;
        virtual double renderer_frequency() const = 0;
        virtual double playground_frequency() const = 0;

    };
}