/*!
 * @author bintjeman
 * @date 24.06.25
 * @name fmt_imgui.hpp
 */

#ifndef BINTJEKIT_RENDERER_FMT_IMGUI_HPP
#define BINTJEKIT_RENDERER_FMT_IMGUI_HPP
#pragma once
#include <SFML/System/Vector2.hpp>
#include <fmt/format.h>
#include <imgui.h>
template <typename T>
struct fmt::formatter<sf::Vector2<T>> {
    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const sf::Vector2<T>& vec, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};
template <>
struct fmt::formatter<ImVec2> {
    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const ImVec2& vec, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};
#endif // BINTJEKIT_RENDERER_FMT_IMGUI_HPP
