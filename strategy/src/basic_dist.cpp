#include <strategy/basic_dist.h>

BasicDist::BasicDist() {

}

std::vector<int> BasicDist::next_action(std::vector<double> inputs) {
    auto ret = std::vector<int>(2, 0);
    auto hit_far_l = inputs[0] > 0;
    auto hit_mid_l = inputs[1] > 0;
    auto hit_c_l = inputs[2] > 0;
    auto hit_c_r = inputs[3] > 0;
    auto hit_mid_r = inputs[4] > 0;
    auto hit_far_r = inputs[5] > 0;

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