/*!
 * @author bintjeman
 * @date 11.06.25
 * @name core.hpp
 */
#ifndef BNJKIT_CORE_CORE_HPP
#define BNJKIT_CORE_CORE_HPP
#pragma once
#include <filesystem>
#include <memory>
#include <spdlog/fwd.h>
#include "module_set.hpp"
#include "bintjekit/utils/time/time.hpp"
namespace bnjkit::conf {
    class Settings;
}
namespace bnjkit::event {
    class EventManager;
}
namespace bnjkit::core {
    class Core {
    public:
        enum class State {
            RUNNING,
            PAUSED,
            STOPPED
        };
        // Constructeurs et déstructeurs
        Core();
        ~Core();
        /*!
         * Initialise Core.
         * Appel l'initialisation de tous les modules membres
         */
        void initialise();
        /*!
         * Configure Core.
         * Appel la configuration de tous les modules membres
         */
        void configure();
        /*!
         * Configure Core.
         * Appel la configuration de tous les modules membres
         */
        void configure(const std::shared_ptr<conf::Settings>& settings);
        /*!
         * Configure Core.
         * Appel la configuration de tous les modules membres
         */
        void configure(const std::filesystem::path& conf_file_path);
        /*!
         * Lance la boucle principale
         */
        void run();
        // Getters
        [[nodiscard]] State state() const;
        [[nodiscard]] conf::Settings& settings() const;
        [[nodiscard]] long engine_frequency() const;
        [[nodiscard]] long renderer_frequency() const;
        [[nodiscard]] long window_frequency() const;
        [[nodiscard]] long engine_effective_frequency() const;
        [[nodiscard]] long renderer_effective_frequency() const;
        [[nodiscard]] long window_effective_frequency() const;
        // Setters
        void set_modules(ModuleSet&& modules);
        void set_state(const State& state);
        void set_engine_frequency(long frequency);
        void set_renderer_frequency(long frequency);
        void set_window_frequency(long frequency);
        void set_settings(const std::shared_ptr<conf::Settings>& settings);
        void save_settings();

    protected:
        // Gestion des états et du temps
        State m_state{State::STOPPED};
        utils::time::Pulser m_engine_pulser;
        utils::time::Pulser m_renderer_pulser;
        utils::time::Pulser m_window_pulser;

    private:
        // Modules
        ModuleSet m_modules;
        // Utilitaires
        std::shared_ptr<conf::Settings> m_settings;
        std::unique_ptr<event::EventManager> m_event_manager;
        std::shared_ptr<spdlog::logger> m_logger;

    public:
        Core(const Core&) = delete;
        Core& operator=(const Core&) = delete;

        // Public static
        static std::string state_to_string(State state);
    };
}
#endif //BNJKIT_CORE_CORE_HPP
