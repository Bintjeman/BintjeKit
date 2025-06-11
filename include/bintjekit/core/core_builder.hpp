/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core_builder.hpp
 */
#ifndef CORE_BUILDER_HPP
#define CORE_BUILDER_HPP
#pragma once
#include <memory>

namespace bnjkit::window {
    class IMainWindow;
}

namespace bnjkit::core {
    class Core;

    class CoreBuilder {
    public:
        CoreBuilder() = default;
        CoreBuilder &set_window_module(std::unique_ptr<window::IMainWindow> window);
        std::unique_ptr<Core> build();

    private:
        std::unique_ptr<window::IMainWindow> m_window;
    };
} // bnjkit::core
#endif //CORE_BUILDER_HPP
