/* Author: Arshiya Rahman
   Version: ????
   For: Teensy 4.1
*/
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "StateController.cpp"

// topLeftLineSensor = A9; //input
// topRightLineSensor = A10; //input
// bottomRightLineSensor = A11; //input
// bottomLeftLineSensor = A12; //input
// leftLidar = A4; //input
// middleLidar = A5; //input
// rightLidar = A6; //input
// leftWheelForward = A0; //output
// leftWheelBackward = A1; //output
// rightWheelForward = A2; //output
// rightWheelBackward = A3; //output

//alternate: just control the power? not sure
int motorSpeed = 650;

int moveSpeed = 650;
int arbitraryDelay = 400;
int arbitraryDistance = 100;

bool allLidars;

StateController sc;
StateS search_state;
StateS attack_state;

//turn the robot to the left
//right wheel goes forward and left wheel goes backward
void turnLeft(int leftSpeed, int rightSpeed) {
    analogWrite(A0, 0);
    analogWrite(A3, 0);
    analogWrite(A1, leftSpeed);
    analogWrite(A2, rightSpeed);
}

//turn the robot to the right
//right wheel goes backward and left wheel goes forward
void turnRight(int leftSpeed, int rightSpeed) {
    analogWrite(A0, leftSpeed);
    analogWrite(A3, rightSpeed);
    analogWrite(A1, 0);
    analogWrite(A2, 0);
}

//reverse
//both wheels go backward
void backUp(int leftSpeed, int rightSpeed) {
    analogWrite(A0, 0);
    analogWrite(A3, rightSpeed);
    analogWrite(A1, leftSpeed);
    analogWrite(A2, 0);
}

//straight-away  movement
//both wheels go forward
void zoom(int leftSpeed, int rightSpeed) {
    analogWrite(A0, leftSpeed);
    analogWrite(A3, 0);
    analogWrite(A1, 0);
    analogWrite(A2, rightSpeed);
}

//shut off all wheels
void allOff() {
    analogWrite(A0, 0);
    analogWrite(A3, 0);
    analogWrite(A2, 0);
    analogWrite(A1, 0);
}

//returns if our left side is on the line or not
bool onLeft() {
    return digitalRead(A12) == 1 || digitalRead(A9) == 1;
}

//returns if our right side is on the line or not
bool onRight() {
    return digitalRead(A11) == 1 || digitalRead(A10) == 1;
}

//left is true, right is false
void aim(boolean isLeft) {
    allOff();
    //if the opponent is on the left
    if (isLeft) {
        //keep turning until we are centered
        while(digitalRead(A5) == 0) {
            turnLeft(moveSpeed, moveSpeed);
        }
        allLidars = true;
        //turn off all wheels to prepare for attack -> needed?
        allOff();
    }
    //if the opponent is on the right
    else {
        //keep turning until we are centered
        while(digitalRead(A5) == 0) {
            turnRight(moveSpeed, moveSpeed);
        }
        allLidars = true;
        //turn off all wheels to perpare for attack -> needed?
        allOff();
    }
}

// //basic roomba-type movement
// void roomba() {
//     //if we hit the left sensor
//     if(onLeft()) {
//         //turn to the right
//         turnRight(moveSpeed, moveSpeed);
//     } 
//     //if we hit the right sensor
//     else if(onRight()) {
//         //turn to the left
//         turnLeft(moveSpeed, moveSpeed);
//     } 
//     //if we're not touching the sensor
//     else {
//         //move forward
//         attack();
//     }
// }
// // //method for looking for the opponent
// void search() {

//     //keep track of whether or not WallI found a robot or not
//     bool spotted = false;

//     //digital or analog write?
//     //make the robot spin

//     /*Optimization for Future
//       - see if can control spin direction based
//         on which sensor lost vision first
//     */
//     turnLeft(moveSpeed, moveSpeed);

//     //can we write this as an interrupt instead?
//     while(!spotted) {
//         if(analogRead(A4) == 0) {
//             spotted = true;
//             aim(true);
//         } else if (analogRead(A5) == 0) {
//             spotted = true;
//             allStop();
//         } else if (analogRead(A6) == 0) {
//             spotted = true;
//             aim(false);
//         }
//     }
//     attack();
// }

//move forward at full force
void attack() {
    //move forward fast
    bool onLine = false;
    zoom(moveSpeed, moveSpeed);

    while (!onLine) {
        if (onLeft()) {
            turnRight(moveSpeed, moveSpeed);
            onLine = true;
        }
        else if (onRight()) {
            turnLeft(moveSpeed, moveSpeed);
            onLine = true;
        }
    }
    backUp(moveSpeed, moveSpeed);
    delay(arbitraryDelay);
    allLidars = false;
}

//true is left, false is right
void spin(bool direction) {
    while (digitalRead(A5) == 0){
        if(direction) {
            turnLeft(moveSpeed, moveSpeed);
        } else {
            turnRight(moveSpeed, moveSpeed);
        }
    }
    allLidars = true;
}

//optimization attempt: always face the robot?
//FIX
void search2() {
    //ideally, robots are facing one another
    //see which lidar loses sight first and turn that way

    while (!allLidars) {
        if(digitalRead(A4) == 0) {
            allLidars = false;
            //left lidar lost vision first
            spin(false);
        } else if (digitalRead(A6) == 0) {
            allLidars = false;
            //right lidar lost vision first
            spin(true);
        } else {
            allLidars = true;
        }
    }
}




//how the hell does this work
void matador() {
    while (digitalRead(A4) == 0) {
        turnRight(moveSpeed, moveSpeed);
    }
    delay(arbitraryDelay);
    while (digitalRead(A9) == 1 && digitalRead(A10) == 1) {
        attack();
    }
    delay(arbitraryDelay);
    while (digitalRead(A4) == 0) {
        turnLeft(moveSpeed, moveSpeed);
    }
    delay(arbitraryDelay);
    while (digitalRead(A9) == 1 && digitalRead(A10) == 1) {
        attack();
    }
    delay(arbitraryDelay);
    while (digitalRead(A5) == 0) {
        turnLeft(moveSpeed, moveSpeed);
    }
    attack();
}




// //"Start" method
// int main() {
//     loop();
// }


void setup() {
    //set the pinmodes for the wheels -> sensors are input by default
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    //start
    Serial.begin(9600);
    
    //attempted state-machine
    sc = StateController();
    search_state = StateS("SEARCH");
    attack_state = StateS("ATTACK");
    search_state.setNext(&attack_state);
    attack_state.setNext(&search_state);
    sc.setCurrent(search_state);
    
    //initial attack
    matador();

}

//"Update" method
void loop() {
    if (&sc.getCurrent() == &search_state) {
        search2();
        if (allLidars) {
            sc.getCurrent().setCondition(true);
        } else {
             sc.getCurrent().setCondition(false);
        }
    } else {
        attack();
        if (allLidars) {
            sc.getCurrent().setCondition(false);
        } else {
             sc.getCurrent().setCondition(true);
        }
    }

}


