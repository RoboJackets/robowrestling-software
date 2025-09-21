#ifndef MOTOR_ACTIONS_HPP
#define MOTOR_ACTIONS_HPP

class motor_actions {
public:
    // Constructor: takes a pointer to an array of motors
    motor_actions(int* motors);

    // You’ll likely add functions here later, e.g. to drive, stop, etc.

private:
    int* motors;  // Pointer to array of motors
};

#endif // MOTOR_ACTIONS_HPP
