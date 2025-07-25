/*!
 * @author bintjeman
 * @date 14.06.25
 * @name fmt_sfml.hpp
 */
#ifndef BNJKIT_COMMONFMT_SFML_HPPFMT_SFML_HPP
#define BNJKIT_COMMONFMT_SFML_HPPFMT_SFML_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <spdlog/fmt/fmt.h>
template<>
struct fmt::formatter<sf::Color> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const sf::Color& clr, FormatContext& ctx) const -> decltype(ctx.out()) {
        // Ajout du mot-clé const ici
        if (clr.a != 255) {
            return fmt::format_to(ctx.out(), "({}, {}, {}, {})", clr.r, clr.g, clr.b, clr.a);
        }
        return fmt::format_to(ctx.out(), "({}, {}, {})", clr.r, clr.g, clr.b);
    }
};

template<typename T>
struct fmt::formatter<sf::Vector2<T> > {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const sf::Vector2<T>& vec, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};
template<typename T>
struct fmt::formatter<sf::Rect<T> > {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const sf::Rect<T>& rect, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "pos:({}, {}), size:({}, {})",
                              rect.position.x, rect.position.y, rect.size.x, rect.size.y);
    }
};
#endif // BNJKIT_COMMONFMT_SFML_HPPFMT_SFML_HPP
