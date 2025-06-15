/*!
 * @author bintjeman
 * @date 15.06.25
 * @name configuration_node.cpp
 */

#include "bintjekit/configuration/configuration_node.hpp"
namespace bnjkit {
    namespace conf {
        ConfigurationNode::ConfigurationNode(nlohmann::json &json_data, const std::string &branch) : json_(json_data),
            branch_(branch) {
        }
        ConfigurationNode ConfigurationNode::get_child(const std::string &key) {
            return ConfigurationNode(json_, branch_.empty() ? key : branch_ + "." + key);
        }
        std::string ConfigurationNode::get_full_key(const std::string &key) const {
            return branch_.empty() ? key : branch_ + "." + key;
        }
    } // conf
} // bnjkit
