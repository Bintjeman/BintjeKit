/*!
 * @author bintjeman
 * @date 14.06.25
 * @name fmt_sfml.hpp
 */

#ifndef FMT_SFML_HPP
#define FMT_SFML_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include <spdlog/fmt/fmt.h>

template<typename T>
struct fmt::formatter<sf::Vector2<T> > {
    constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const sf::Vector2<T> &vec, FormatContext &ctx) -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};

template<typename T>
struct fmt::formatter<sf::Rect<T> > {
    constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const sf::Rect<T> &rect, FormatContext &ctx) -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "pos:({}, {}), size:({}, {})",
                              rect.position.x, rect.position.y, rect.size.x, rect.size.y);
    }
};

#endif //FMT_SFML_HPP
