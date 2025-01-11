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
export module bik.time:pulser;
import :clock;
namespace bik::time {
    export template<typename Precision = std::chrono::milliseconds>
    class Pulser : public Clock<Precision> {
    public:
        using Duration = typename Precision::duration;
        using Period = typename Precision::period;
        Pulser();
        virtual ~Pulser();
        bool pulse();
        bool operator ()();
        void set_frequency(double frequency);
        void set_interval(Duration interval);
        [[nodiscard]] auto interval() const;
        [[nodiscard]] auto effective_interval() const;
        [[nodiscard]] auto effective_frequency() const;
        void each(bool each);

    private:
        Duration interval_;
        Duration effective_interval_;
        bool each_ = false;
    };
}
