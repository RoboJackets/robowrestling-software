#ifndef FIGURE_EIGHT
#define FIGURE_EIGHT 

#include <Behaviors/Nodes/Node.h>
#include <Arduino.h>

template<typename T, typename U>
class FigureEight : public BT::Node<T,U> {
public: 
    FigureEight(int speed, int time2Switch) : BT::Node<T,U>(0,0), _speed(speed),
        _time2Switch(time2Switch) {
        _lastTime = millis(); 

    }


    U Run(T state) {
        if (millis() - _lastTime > _time2Switch) {
            dir = !dir; 
            _lastTime = millis(); 
        }

        U output; 
        output.currentRightMotorPow = (dir) ? _speed : 0; 
        output.currentLeftMotorPow = (dir) ? 0 : _speed; 

        return output; 
    }

private: 
    int _speed = 0; 
    uint32_t _time2Switch;
    uint32_t _lastTime = 0;
    bool dir = true;  // true -> right, false -> left

}; 


#endif 