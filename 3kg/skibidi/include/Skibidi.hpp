#ifndef SKIBIDI_HPP_
#define SKIBIDI_HPP_

#include <map>
#include <utility>
#include "Sensors/DoubleLineSensor.hpp"

enum LeftRight { LEFT, RIGHT };

class Skibidi {
    private:
        std::map<LeftRight, DoubleLineSensor*> line_sensors;
    public:
        Skibidi();
};

#endif // SKIBIDI_HPP_
