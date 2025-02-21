#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"

algorithms :: algorithms(robot_actions *robot, world_state *world, timer* thymer) {
    this -> robot = robot;
    this -> world = world;
    this -> thymer = thymer;
    app_state = GO_STRAIGHT;
}

void algorithms :: turn_test() {
    //if the timer has gone off
    if (thymer -> check_action_time()) {
        //set the timer
        thymer -> set_action_timer(200);
        //reverse state
        app_state = app_state == GO_STRAIGHT ? GO_BACKWARDS : GO_STRAIGHT;
        //brake momentarily
        robot -> brake();
        return;
    }
    //if the timer has not gone off
    if (app_state == GO_STRAIGHT) {
        robot -> drive_forward(100);
    } else {
        robot -> drive_backward(100);
    } 
}

void algorithms :: draw() {
    approach_line();
}

int algorithms :: approach_line() {
    //if the timer started
    if (!thymer -> check_action_time()) {
        //if the state is turn
        if (app_state == TURN) {
            //turn
            robot -> turn_left(150);
        //if the state is to go backwards
        } else if (app_state == GO_BACKWARDS) {
            //go backwards
            robot -> drive_backward(150);
        }
        //return
        return 1;
    //if there's no timer and the state is to go backwards (should be if the backwards timer finished)
    } else if (app_state == GO_BACKWARDS) {
        //turn left
        robot -> brake();
        //set turn left timer
        thymer -> set_action_timer(30);
        //set state to turn left
        app_state = TURN;
        //return
        return 1;
    }
    //if neither of these are true (we're back to default behavior)
    if (world -> line_check() == OFF) {
        //go forwards
        robot -> drive_forward(0);
    //if we found a line
    } else {
        //drive backwards
        robot -> brake();
        //set backwards timer
        thymer -> set_action_timer(50);
        //set state to go backwards
        app_state = GO_BACKWARDS;
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
    return 0;
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