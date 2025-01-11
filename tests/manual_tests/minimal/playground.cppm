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
export module min.playground;
export import bik.playground;
namespace min {
export class PlayGround: public bik::playground::BasePlayGround {
  public:
    PlayGround() = default;
    void update() override{
      counter_++;
    }
    long long int get_counter() const {
      return counter_;
    }
    void set_target(long long int target) {
      this->target_ = target;
    }
    bool over() {
      counter_>=target_;
    }
    private:
      long long int counter_ = 0;
      long long int target_ = 1'000'000'000'000'000'000;
};
}
