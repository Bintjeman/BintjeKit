/*!
 * @file logger_extension.cppm
 * @author bintjeman
 * @date 07.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <spdlog/fmt/fmt.h>
export module bik.logger:extension;
namespace fmt {
    export template<typename T>
    struct fmt::formatter<sf::Vector2<T> > {
        template<typename ParseContext>
        constexpr auto parse(ParseContext &ctx) const {
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const sf::Vector2<T> &v, FormatContext &ctx) const {
            return fmt::format_to(ctx.out(), "Vector2({}, {})", v.x, v.y);
        }
    };

    export template<typename T>
    struct fmt::formatter<sf::Rect<T> > {
        template<typename ParseContext>
        constexpr auto parse(ParseContext &ctx) const {
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const sf::Rect<T> &r, FormatContext &ctx) const {
            return fmt::format_to(ctx.out(), "Rect({}, {}, {}, {})", r.position.x, r.position.x,
                                  r.size.x, r.size.y);
        }
    };

    export template<>
    struct fmt::formatter<sf::Color> {
        template<typename ParseContext>
        constexpr auto parse(ParseContext &ctx) const {
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const sf::Color &clr, FormatContext &ctx) const {
            if (clr.a == 255) {
                return fmt::format_to(ctx.out(), "Color({}, {}, {})", clr.r, clr.g, clr.b);
            } else {
                return fmt::format_to(ctx.out(), "Color({}, {}, {}, {})", clr.r, clr.g, clr.b,
                                      clr.a);
            }
        }
    };
} // namespace fmt
