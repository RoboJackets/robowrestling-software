#include <strategy/kevin_brody.h>
#include <iostream>

KevinBrodyStrategy::KevinBrodyStrategy() {
    state = IDLE;
}

// remember to use IMU sensor somehow
std::vector<int> KevinBrodyStrategy::next_action(SensorData input) {
    int output[] = {0, 0};
    state = update_state(input);
    switch (state) {
    case FORWARD:
        output[0] = 100;
        output[1] = 100;
        //        std::cout << "FORWARD" << std::endl;

        break;
    case BACK:
        output[0] = -100;
        output[1] = -100;
        break;
    // fast af turn
    case TURN_LEFT:
        output[0] = 50;
        output[1] = -50;
        break;
    case TURN_RIGHT:
        output[0] = -50;
        output[1] = 50;
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

KevinBrodyStrategy::State KevinBrodyStrategy::update_state(SensorData input) {
    // TODO: implement, you can delete the stuff below
    // input.dist_buffer_[2] and 3 are the front ones
    // 0 and 1 are left
    // 4 and 5 are right
    // units are in centimeters
    // 1.5 meter
    // front left front right for the line sensors [0] [1]
    // left to right
    
    if ((input.line_buffer_[0] > 0 || input.line_buffer_[1] > 0)) 
    {
        std::cout << "line " << input.dist_buffer_[0] << " " << input.dist_buffer_[1] << std::endl;
       return BACK;
    }
    // else if ((input.line_buffer_[0] < 100 || input.line_buffer_[1] < 100)) 
    // {
    //     std::cout << "slow down " << input.dist_buffer_[0] << " " << input.dist_buffer_[1] << std::endl;
    //    return BACK;
    // }
    else if (input.dist_buffer_[2] < 150 || input.dist_buffer_[3] < 150) { //front ones // change too 100 for awesome juke
         std::cout << "front " << input.dist_buffer_[2] << " " << input.dist_buffer_[3] << std::endl;
         return FORWARD;

    }
    else if (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150){
        std::cout << "left " << input.dist_buffer_[0] << " " << input.dist_buffer_[1] << std::endl;
    return TURN_LEFT;
    }
    // Sensor far or mid right hit - far dist
    else if (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150){
        std::cout << "right " << input.dist_buffer_[4] << " " << input.dist_buffer_[5] << std::endl;
        return TURN_RIGHT;
    } else {
          std::cout << "SEARCH " << input.dist_buffer_[2] << " " << input.dist_buffer_[3] << std::endl;
        return SEARCH;
        
        //return FORWARD;
    }
    
    // else if (input.dist_buffer_[2] < 150 || input.dist_buffer_[3] < 150) {
        
    // } else if ((input.line_buffer_[1] > 190 || input.line_buffer_[1] > 190)
    //      && (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150) // left
    //      && (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150)) { // right
    //      return BACK;
    // } 

}
