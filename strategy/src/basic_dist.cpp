#include <strategy/basic_dist.h>

BasicDist::BasicDist() {

}

std::vector<int> BasicDist::next_action(SensorData input) {
    auto ret = std::vector<int>(2, 0);
    auto hit_far_l = input.dist_buffer_[0] > 0;
    auto hit_mid_l = input.dist_buffer_[1] > 0;
    auto hit_c_l = input.dist_buffer_[2] > 0;
    auto hit_c_r = input.dist_buffer_[3] > 0;
    auto hit_mid_r = input.dist_buffer_[4] > 0;
    auto hit_far_r = input.dist_buffer_[5] > 0;

    if (hit_c_r && hit_c_l) {
        ret[0] = 100;
        ret[1] = 100;
    } else if (hit_far_l || hit_mid_l) {
        ret[0] = 100;
        ret[1] = 0;
    } else if (hit_far_r || hit_mid_r) {
        ret[0] = 0;
        ret[1] = 100;
    } else {
        ret[0] = 50;
        ret[1] = -50;
    }

    return ret;

}