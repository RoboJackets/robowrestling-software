#include <strategy/kevin_brody_enemy.h>
#include <iostream>

KevinBrodyStrategyEnemy::KevinBrodyStrategyEnemy() {
    state = IDLE;
}

// remember to use IMU sensor somehow
std::vector<int> KevinBrodyStrategyEnemy::next_action(SensorData input) {
    int output[] = {0, 0};
    state = update_state(input);
    switch (state) {
    case FORWARD:
        output[0] = 100;
        output[1] = 100;
        break;
    case BACK:
        output[0] = -50;
        output[1] = -50;
        break;
    // fast af turn
    case TURN_LEFT:
        output[0] = 0;
        output[1] = 100;
        break;
    case TURN_RIGHT:
        output[0] = 100;
        output[1] = 0;
        break;
    case STOP:
        output[0] = 0;
        output[1] = 0;
        break;
    // turns in place
    case SEARCH:
        output[0] = 50;
        output[1] = -50;
        break;
    default:
        break;
    }

    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

KevinBrodyStrategyEnemy::State KevinBrodyStrategyEnemy::update_state(SensorData input) {
    // TODO: implement, you can delete the stuff below
    // input.dist_buffer_[2] and 3 are the front ones
    // 0 and 1 are left
    // 4 and 5 are right
    // units are in centimeters
    // 1.5 meter
    // front left front right for the line sensors [0] [1]
    // left to right
    
    std::cout << input.line_buffer_[0] << "\n";
    
   /* line sensor hit
   if (input.line_buffer_[0] < 255 || input.line_buffer_[1] < 255){
        std::cout << "Line Sensor Hit\n";
        return BACK;
        } */
    // Sensor center left or right hit
    else if (input.dist_buffer_[2] < 176 || input.dist_buffer_[3] < 176) { //front ones
        //std::cout << "Sensor center left or right hit\n";
        return FORWARD;
        } 
    Sensor far or mid left hit - close dist
    else if (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150){
        std::cout << "Sensor far or mid left hit - close dist\n";
        std::cout << "Left: " << input.dist_buffer_[0] << ", Right: " << input.dist_buffer_[1] << "\n";
        return FORWARD;
        }
    // Sensor far or mid right hit - close dist
    else if (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150){
        std::cout << "Sensor far or mid right hit - close dist\n";
        return FORWARD;
        }
    // Sensor far or mid left hit - far dist
    else if (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150){
        std::cout << "Sensor far or mid left hit - far dist\n";
        return TURN_LEFT;
        }
    // Sensor far or mid right hit - far dist
    else if (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150){
        std::cout << "Sensor far or mid right hit - far dist\n";
        return TURN_RIGHT;
        } */
    // No sensor input
    else {
        std::cout << "No sensor input\n";
        return SEARCH;
    }
}
