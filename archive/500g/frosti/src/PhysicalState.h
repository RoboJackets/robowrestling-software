#ifndef PHYSICAL_STATE_H
#define PHYSICAL_STATE_H

#include "Vector2.h"

struct PhysicalState {
    Vector2<double> pos_{0.0, 0.0};
    Vector2<double> vel_{0.0, 0.0};
};

#endif