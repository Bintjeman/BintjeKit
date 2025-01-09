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
        using Duration = std::chrono::duration<double>;
        Pulser();
        virtual ~Pulser();
        bool pulse();
        bool operator ()();
        void set_frequency(double frequency);
        void set_interval(std::chrono::duration<double> interval);
        long long interval() const;
        long long effective_interval() const;
        void each(bool each);

    private:
        long long interval_;
        long long effective_interval_;
        bool each_ = false;
    };
}
