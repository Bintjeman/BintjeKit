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
export module min.playground;
export import bik.playground;
import bik.logger;
import bik.time;
namespace min {
    export class PlayGround : public bik::playground::BasePlayGround {
    public:
        PlayGround() {
            clock_.start();
        };

        void update() override {
            counter_++;
            if (counter_ % 1'000 == 0) {
                auto elapsed = clock_.elapsed();
                std::cout << "counter: " << counter_ << ", elapsed: " << elapsed << "\n";
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
                std::cout << "counter: " << counter_ << ", elapsed: " << elapsed_d << " S\nFINISHED!";
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
