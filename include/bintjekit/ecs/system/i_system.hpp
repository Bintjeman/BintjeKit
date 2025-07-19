/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_system.hpp
 */

#ifndef  BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
#define  BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
#pragma once
#include <string>

namespace bnjkit::engine {
    class IEngine;
}

namespace bnjkit::ecs {
    class ISystem {
    public:
        ISystem();
        virtual ~ISystem();
        virtual void initialize(engine::IEngine& engine);
        virtual void update(engine::IEngine& engine);
        virtual void cleanup(engine::IEngine& engine);
        [[nodiscard]] virtual std::string name() const;
    };
}

#endif // BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
