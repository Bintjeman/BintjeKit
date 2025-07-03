/*!
 * @author bintjeman
 * @date 11.06.25
 * @name i_module.cpp
 */

#include "bintjekit/core/i_module.hpp"
bnjkit::core::IModule::IModule() = default;
bnjkit::core::IModule::~IModule() = default;

void bnjkit::core::IModule::initialise() {
}

void bnjkit::core::IModule::configure() {
}
void bnjkit::core::IModule::on_quit() {
}
void bnjkit::core::IModule::set_settings(const conf::Node& settings) {
    nlohmann::json tmp_json;
    conf::Node tmp_json_arg = settings;
    if (!m_settings.get_json().empty()) {
        tmp_json = m_settings.get_json();
        tmp_json_arg.merge_with_json(tmp_json);
    }
    m_settings = tmp_json_arg;
}
void bnjkit::core::IModule::set_custom(const conf::Node& settings) {
    nlohmann::json tmp_json;
    conf::Node tmp_json_arg = settings;
    if (!m_custom_settings.get_json().empty()) {
        tmp_json = m_custom_settings.get_json();
        tmp_json_arg.merge_with_json(tmp_json);
    }
    m_custom_settings = tmp_json_arg;
}
