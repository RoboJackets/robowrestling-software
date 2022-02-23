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
        output[0] = 5;
        output[1] = 5;
        break;
    case BACK:
        output[0] = -100;
        output[1] = -100;
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
    case LEFT_BACK:
        output[0] = -50;
        output[1] = -100;
        break;
    case RIGHT_BACK:
        output[0] = -100;
        output[1] = -50;
        break;
    case STOP:
        output[0] = 0;
        output[1] = 0;
        break;
    // turns in place
    case SEARCH:
        output[0] = 25;
        output[1] = -25;
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

    /* 
    LINE SENSORS
    both sensors = back
    left sensor = right back
    right sensor = left back
    
    DISTANCE SENSORS
    Both front sensors = forward
    Both left sensors(close) = forward
    Both left sensors(far) = turn left
    Both right sensors(close) = forward
    Both right sensors(far) = turn left
    Mid left and left right sensors(close) = left forward
    Mid left and left right sensors(far) = turn left
    Mid right and right sensors(close) = right forward
    Mid right and right sensors(far) = turn right
    */
    
    std::cout << "( " << input.dist_buffer_[0] << ", " << input.dist_buffer_[1] <<  ", " << input.dist_buffer_[2] << ", " <<  input.dist_buffer_[3] << ", " <<  input.dist_buffer[4] << ", " <<  input.dist_buffer_[5] << " )\n";
   // both line sensor hit
   if (input.line_buffer_[0] > 0 || input.line_buffer_[1] > 0){
        return BACK;
        } 
    left line sensor hit
    else if(input.line_buffer_[0] > 0) {
        return RIGHT_BACK;
    }
    //right line sensor hit
    else if(input.line_buffer_[1] > 0) {
        return LEFT_BACK;
    }
    // Sensor center left or right hit
    else if ((input.dist_buffer_[2] < 150 || input.dist_buffer_[3] < 150)) { //front ones
        return FORWARD;
        } 
    // Sensor far or mid left hit - close dist
    else if (input.dist_buffer_[0] < 40 || input.dist_buffer_[1] <= 40){
        return FORWARD;
        }
    // Sensor far or mid right hit - close dist
    else if (input.dist_buffer_[4] < 40 || input.dist_buffer_[5] < 40){
        return FORWARD;
        }
    // Sensor far or mid left hit - far dist
    else if (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150){
        return TURN_LEFT;
        }
    // Sensor far or mid right hit - far dist
    else if (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150){
        return TURN_RIGHT;
        }
    // No sensor input
    else {
        return FORWARD;
    }
}

