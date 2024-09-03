#ifndef SKIBIDI_HPP_
#define SKIBIDI_HPP_

#include <map>
#include <utility>
#include "Sensors/DoubleLineSensor.hpp"

enum Position { FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT };

class Skibidi {
    private:
        std::map<Position, DoubleLineSensor*> line_sensors;
    public:
        Skibidi();
};

#endif // SKIBIDI_HPP_
