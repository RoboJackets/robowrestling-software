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
        output[0] = 50;
        output[1] = 50;
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
    case STOP:
        output[0] = 0;
        output[1] = 0;
        break;
    // turns in place
    case SEARCH:
        output[0] = 100;
        output[1] = -100;
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
<<<<<<< HEAD
    std::cout  << input.line_buffer_[0] << "\n";
    if (input.dist_buffer_[2] < 1000 || input.dist_buffer_[3] < 1000) { //front ones
        return FORWARD;
    } else if ((input.line_buffer_[0] < 10 || input.line_buffer_[1] < 10)) 
=======
    
     if ((input.line_buffer_[0] < 100 || input.line_buffer_[1] < 100)) 
>>>>>>> 561e90963a078c1564bd22778513957e6fcfc6ff
    {
       return BACK;
    } //else if (input.dist_buffer_[0] < 100 || input.dist_buffer_[0] < 100)
    else if (input.dist_buffer_[2] < 160 || input.dist_buffer_[3] < 160) { //front ones
         std::cout << "front " << input.dist_buffer_[2] << " " << input.dist_buffer_[3] << std::endl;
         return FORWARD;

    }
    else if (input.dist_buffer_[0] < 50 || input.dist_buffer_[1] < 50) { //left ones
        std::cout << "left " << std::endl;
        return TURN_LEFT;
    }
    else if (input.dist_buffer_[4] < 50 || input.dist_buffer_[5] < 50) { //right ones
        return TURN_RIGHT;
    }
    
    // else if (input.dist_buffer_[2] < 150 || input.dist_buffer_[3] < 150) {
        
    // } else if ((input.line_buffer_[1] > 190 || input.line_buffer_[1] > 190)
    //      && (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150) // left
    //      && (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150)) { // right
    //      return BACK;
    // } 
    else {
          std::cout << "STOP " << input.dist_buffer_[2] << " " << input.dist_buffer_[3] << std::endl;
        return STOP;
        
        //return FORWARD;
    }
}
