#include "Robot/robotActions.hpp"

RobotActions::RobotActions(MotorDriver *blDriver, MotorDriver *flDriver, MotorDriver *frDriver, MotorDriver *brDriver) {
    this->flDriver = flDriver;
    this->frDriver = frDriver;
    this->blDriver = blDriver;
    this->brDriver = brDriver;

    this->prev_action = NoneAction;
    this->speed = 0;
}

// Forward attacking curve
void RobotActions::Attack(EnemyPositions pos) {
    // Future Note: Pins set the direction and speed of the robot
    // Make sure to ramp values for speed to avoid jump
    if (this->prev_action == ForwardAction && pos == EnemyFront) {
        this->speed += 5;
        if (this->speed > 200) {
            this->speed = 200;
        }
    } else {
        // Decelerate
        this->speed -= 20;
        if (this->speed < 10) {
            this->speed = 10;
        }
    }

    // Setting drivers after forward
    flDriver->setDirection(0);
    flDriver->setSpeed(this->speed);

    blDriver->setDirection(0);
    blDriver->setSpeed(this->speed);

    frDriver->setDirection(0);
    frDriver->setSpeed(this->speed);

    brDriver->setDirection(0);
    brDriver->setSpeed(this->speed);

    // Curve towards opp. Overwrite speeds to -10 for curve. Change for more
    if (pos == EnemyFR) {
        frDriver->setDirection(0);
        frDriver->setSpeed(this->speed - 10);

        brDriver->setDirection(0);
        brDriver->setSpeed(this->speed - 10);
    } else if (pos == EnemyFL) {
        flDriver->setDirection(0);
        flDriver->setSpeed(this->speed - 10);

        blDriver->setDirection(0);
        blDriver->setSpeed(this->speed - 10);
    }

    this->prev_action = ForwardAction;
}

// Just straight forward
void RobotActions::Forward(int spd) {
    flDriver->setDirection(0);
    flDriver->setSpeed(spd);

    blDriver->setDirection(0);
    blDriver->setSpeed(spd);

    frDriver->setDirection(0);
    frDriver->setSpeed(spd);

    brDriver->setDirection(0);
    brDriver->setSpeed(spd);
}

void RobotActions::Backwards(int spd) {
    flDriver->setDirection(1);
    flDriver->setSpeed(spd);

    blDriver->setDirection(1);
    blDriver->setSpeed(spd);

    frDriver->setDirection(1);
    frDriver->setSpeed(spd);

    brDriver->setDirection(1);
    brDriver->setSpeed(spd);
    this->prev_action = BackAction;
}

void RobotActions::Left(int spd) {
    flDriver->setDirection(0);
    flDriver->setSpeed(spd);

    blDriver->setDirection(0);
    blDriver->setSpeed(spd);

    frDriver->setDirection(1);
    frDriver->setSpeed(spd);

    brDriver->setDirection(1);
    brDriver->setSpeed(spd);
    this->prev_action = LeftAction;
}

void RobotActions::Right(int spd) {
    flDriver->setDirection(1);
    flDriver->setSpeed(spd);

    blDriver->setDirection(1);
    blDriver->setSpeed(spd);

    frDriver->setDirection(0);
    frDriver->setSpeed(spd);

    brDriver->setDirection(0);
    brDriver->setSpeed(spd);
    this->prev_action = RightAction;
}
void RobotActions::Circle() {
    flDriver->setDirection(0);
    flDriver->setSpeed(40);

    blDriver->setDirection(0);
    blDriver->setSpeed(40);

    frDriver->setDirection(1);
    frDriver->setSpeed(40);

    brDriver->setDirection(1);
    brDriver->setSpeed(40);
    this->prev_action = CircleAction;
}



// Old Code for attacking forwards
// Curving towards opp, max turn 85 for slower wheel
    // if (pos == MidR) {
    //     if (this->speed - 15 < 0) {
    //         flDriver->setSpeed(0);
    //         blDriver->setSpeed(0);
    //     } else {
    //         flDriver->setSpeed(this->speed - 15);
    //         blDriver->setSpeed(this->speed - 15);
    //     }
    // } else if (pos == MidL) {
    //     if (this->speed - 15 < 0) {
    //         frDriver->setSpeed(0);
    //         blDriver->setSpeed(0);
    //     } else {
    //         frDriver->setSpeed(this->speed - 15);
    //         brDriver->setSpeed(this->speed - 15);
    //     }
    // } 