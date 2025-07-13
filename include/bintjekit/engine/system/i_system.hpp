/*!
 * @author bintjeman
 * @date 13.07.25
 * @name i_system.hpp
 */

#ifndef  BINTJEKIT_ENGINE_SYSTEM_I_SYSTEM_HPP
#define  BINTJEKIT_ENGINE_SYSTEM_I_SYSTEM_HPP
#pragma once

namespace bnjkit::engine {
    class World;

    class ISystem {
    public:
        virtual ~ISystem() = default;

        // Initialisation du système
        virtual void initialize(World& world) = 0;

        // Mise à jour du système
        virtual void update(World& world) = 0;

        // Nettoyage du système
        virtual void cleanup(World& world) = 0;

        // Activation/désactivation du système
        virtual void enable() { m_enabled = true; }
        virtual void disable() { m_enabled = false; }
        [[nodiscard]] bool is_enabled() const { return m_enabled; }

        // Priorité du système (ordre d'exécution)
        [[nodiscard]] virtual int get_priority() const { return 0; }

    private:
        bool m_enabled{true};
    };
}

#endif // BINTJEKIT_ENGINE_SYSTEM_I_SYSTEM_HPP
