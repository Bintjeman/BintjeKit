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

    class ISystem {
    public:
        ISystem();
        virtual ~ISystem();

        // Initialisation du système
        virtual void initialize(IEngine& world);

        // Mise à jour du système
        virtual void update(IEngine& world);

        // Nettoyage du système
        virtual void cleanup(IEngine& world);
        [[nodiscard]] virtual std::string name() const = 0;

    protected:
        std::string m_name;
    };
}

#endif // BINTJEKIT_ECS_SYSTEM_I_SYSTEM_HPP
