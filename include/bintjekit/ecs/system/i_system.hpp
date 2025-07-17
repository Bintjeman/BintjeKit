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

// namespace bnjkit::engine {
//     class IEngine;
// }
namespace bnjkit::ecs {
    // class ISystem {
    // public:
    //     ISystem();
    //     virtual ~ISystem();
    //     // Initialisation du système
    //     virtual void initialize(engine::IEngine& engine);
    //     // Mise à jour du système
    //     virtual void update(engine::IEngine& engine);
    //     // Nettoyage du système
    //     virtual void cleanup(engine::IEngine& engine);
    //     [[nodiscard]] virtual std::string name() const;
    //
    // };
    class ISystem {
    public:
        inline ISystem() = default;
        inline virtual ~ISystem() = default;
        inline virtual void initialize(engine::IEngine& engine[[maybe_unused]]) {}
        inline virtual void update(engine::IEngine& engine[[maybe_unused]]) {}
        inline virtual void cleanup(engine::IEngine& engine[[maybe_unused]]) {}
        [[nodiscard]] inline virtual std::string name() const { return "ISystem"; }
    };
}

#endif // BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
