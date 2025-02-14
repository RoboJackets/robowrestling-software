#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"

algorithms :: algorithms(robot_actions *robot, world_state *world) {
    this -> robot = robot;
    this -> world = world;
    app_line_state = GO_STRAIGHT;
}

void algorithms :: draw() {
    approach_line();
}

int algorithms :: approach_line() {
    if (world -> line_check() == OFF) {
        robot -> drive_forward(100);
    } else if (app_line_state = GO_STRAIGHT) {
        robot -> drive_backward(150);
        app_line_state = TURN;
    } else {
        robot -> turn_left(150);
        app_line_state = GO_STRAIGHT;
    }
    return 0;
}

int algorithms :: forward_safe() {
    if (world -> enemy_pos() == FRONT || world -> enemy_pos() == CLOSE_MID) {
        robot -> drive_forward(100);
    } else if (world -> enemy_pos() == CLOSE_MID) {
        robot -> drive_forward(200);
    } else {
        robot -> brake();
    }
}
//returns 1 on success, 0 on failure
int algorithms :: turn_towards() {
    if (world -> enemy_pos() == LEFT) {
        robot -> turn_left(150);
        return 1;
    } else if(world -> enemy_pos() == FRONT_LEFT) {
        robot -> turn_left(100);
        return 1;
    } else if (world -> enemy_pos() == CLOSE_MID_LEFT) {
        robot -> turn_left(50);
        return 1;
    } else if (world -> enemy_pos() == RIGHT) {
        robot -> turn_right(150);
        return 1;
    } else if (world -> enemy_pos() == FRONT_RIGHT) {
        robot -> turn_right(100);
        return 1;
    } else if (world -> enemy_pos() == CLOSE_MID_RIGHT) {
        robot -> turn_right(50);
        return 1;
    }
    return 0;
}