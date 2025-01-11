/*!
 * @file components.cppm
 * @author bintjeman
 * @date 11.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module bik.common:component;
namespace bik::component {
    export class BaseComponent {
        public:
        inline BaseComponent() = default;
        inline virtual ~BaseComponent() {}
    };
}
