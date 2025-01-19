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
        [[nodiscard]] virtual double renderer_effective_frequency() const = 0;
        [[nodiscard]] virtual double playground_effective_frequency() const = 0;
        [[nodiscard]] virtual double renderer_target_frequency() const =0;
        [[nodiscard]] virtual double playground_target_frequency() const =0;
    };
}
