/*!
 * @file pulser.cppm
 * @author bintjeman
 * @date 09.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
module;
#include <chrono>
#include "using.hpp"
export module bik.time:pulser;
import :clock;
namespace bik::time {
    export class Pulser final : public Clock {
    public:
        Pulser();
        ~Pulser() override;
        bool pulse();
        bool operator ()();
        void set_frequency(double frequency);
        void set_interval(DurationDef interval);
        [[nodiscard]] auto interval() const;
        [[nodiscard]] auto frequency() const;
        [[nodiscard]] auto effective_interval() const;
        [[nodiscard]] auto effective_frequency() const;
        void each(bool each);

    private:
        DurationDef interval_;
        DurationDef effective_interval_;
        bool each_ = false;
    };
}
