/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_module.cpp
 */

#include "bintjekit/core/i_module.hpp"

namespace bnjkit::core {
    IModule::IModule() = default;
    IModule::~IModule() = default;
    void IModule::initialise() {}
    void IModule::configure() {}
    void IModule::on_quit() {}
    void IModule::configure(const conf::Node& settings, const conf::Node& custom_settings) {
        set_settings(settings);
        if (!custom_settings.get_json().empty()) {
            set_custom(custom_settings);
        }
        configure();
    }
    void IModule::set_settings(const conf::Node& settings) {
        conf::Node tmp_json_arg = settings;
        if (!m_settings.get_json().empty()) {
            const nlohmann::json tmp_json = m_settings.get_json();
            tmp_json_arg.merge_with_json(tmp_json);
        }
        m_settings = tmp_json_arg;
    }
    void IModule::set_custom(const conf::Node& settings) {
        conf::Node tmp_json_arg = settings;
        if (!m_custom_settings.get_json().empty()) {
            const nlohmann::json tmp_json = m_custom_settings.get_json();
            tmp_json_arg.merge_with_json(tmp_json);
        }
        m_custom_settings = tmp_json_arg;
    }
}
