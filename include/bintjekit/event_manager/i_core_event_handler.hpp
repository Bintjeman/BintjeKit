/*!
 * @author bintjeman
 * @date 16.06.25
 * @name ICoreEventHandler.hpp
 */
#ifndef BNJKIT_EVENT_ICOREEVENTHANDLER_HPP
#define BNJKIT_EVENT_ICOREEVENTHANDLER_HPP
#pragma once
#include <memory>
#include <spdlog/fwd.h>
#include "SFML/Window/Event.hpp"
#include "bintjekit/core/i_module.hpp"

namespace bnjkit::core {
    class Core;
}

namespace bnjkit::event {
    class ICoreEventHandler : public core::IModule {
    public:
        ICoreEventHandler();
        ~ICoreEventHandler() override;
        virtual void set_core(core::Core* core);
        virtual void on_sfml_event(const sf::Event& event) =0;
        [[nodiscard]] std::string name() const override;

    protected:
        core::Core* m_core;
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
#endif // BNJKIT_EVENT_ICOREEVENTHANDLER_HPP
