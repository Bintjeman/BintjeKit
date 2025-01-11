/*!
 * @file playground.cppm
 * @author bintjeman
 * @date 11.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <iostream>
#include <nlohmann/json.hpp>
#include "tools/logger/logger_define.hpp"
export module min.playground;
export import bik.playground;
import bik.logger;
import bik.settings;
import bik.time;
namespace min {
    export class PlayGround : public bik::playground::BasePlayGround {
    public:
        PlayGround() {
            clock_.start();
        };

        void initialize() override {
            target_ = settings_.get_or_set("/MinimalTest/Target"_json_pointer, 1'000'000'000);
        }

        void update() override {
            counter_++;
            if (counter_ % 1'000 == 0) {
                auto elapsed = clock_.elapsed();
                auto seconds = bik::time::to_seconds(elapsed);
                auto frequency = bik::time::to_frequency(elapsed);
                LOGGER->trace("counter: {}, elapsed: {}, frequency: {}", counter_, seconds, frequency);
            }
        }

        long long int get_counter() const {
            return counter_;
        }

        void set_target(long long int target) {
            this->target_ = target;
        }

        bool over() {
            if (counter_ >= target_) {
                auto elapsed = clock_.elapsed();
                double elapsed_d = static_cast<double>(elapsed) / 1'000'000'000.0;
                LOGGER->info("counter: {}, elapsed: {}", counter_, elapsed_d);
                return true;
            }
            return false;
        }

    private:
        long long int counter_ = 0;
        long long int target_ = 10'000;
        bik::time::Clock<> clock_;
    };
}
