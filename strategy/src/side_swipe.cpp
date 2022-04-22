#include <strategy/side_swipe.h>

SideSwipe::SideSwipe() {
    mState = IDLE;
    targetLock = false;
    currentAngle = 0.0;
    lastTime = timeNow(); 
}






std::vector<int> SideSwipe::next_action(SensorData input) {
    int output[] = {0,0};

    /* compute angle */
    double elapsedTime = duration(timeNow() - lastTime) / 1000000000.0;
    currentAngle += input.z_gyro_ * elapsedTime;
    
    /*if (currentAngle > 6.28) {
        currentAngle -= 6.28;
    } else if (currentAngle < -6.28) {
        currentAngle += 6.28;
    }*/

    if (currentAngle < 3.14) {
        output[0] = -2;
        output[1] = 2;
    } else {
        output[0] = 0;
        output[1] = 0;
    }
    lastTime = timeNow();
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}


SideSwipe::State SideSwipe::updateState(SensorData input) {
    int frontDist = ((input.dist_buffer_[2] + input.dist_buffer_[3]) / 2);
    int leftDist  = ((input.dist_buffer_[0] + input.dist_buffer_[1]) / 2);
    int rightDist = ((input.dist_buffer_[4] + input.dist_buffer_[5]) / 2);

    int lineSensor = ((input.line_buffer_[0] + input.line_buffer_[1]) / 2);

    if (lineSensor > 125) {
        targetLock = false; 
        return BOUNDRY;
    }

    if (leftDist < frontDist && leftDist < rightDist && !targetLock) {
        return SEARCH_LEFT;
    } else if (rightDist < frontDist && rightDist < rightDist && !targetLock) {
        return SEARCH_RIGHT;
    } else {
        if (frontDist > 50) {
            return APPROACH;
        }

        if (frontDist < 50) {
            targetLock = true; 
            return CURVE; 
        }
    }

    if (targetLock) {
        


    }

    

    

    return IDLE; 
}