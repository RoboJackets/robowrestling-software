#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"

algorithms :: algorithms(robot_actions *robot, world_state *world, timer* thymer) {
    this -> robot = robot;
    this -> world = world;
    this -> thymer = thymer;
    app_state = GO_STRAIGHT;
}

void algorithms :: back_and_forth() {
    if (thymer -> check_action_time()) {
        if (app_state == GO_STRAIGHT) {
            app_state = GO_BACKWARDS;
        } else {
            app_state = GO_STRAIGHT;
        }
        thymer -> set_action_timer(300);
        robot -> brake();
        return;
    }
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
    //if the timer went off (action has completed)
    if (app_state == GO_BACKWARDS && thymer -> check_action_time()) {
        app_state = GO_STRAIGHT;
        robot -> brake();
    }
    //if a timer isn't currently going off
    //if the current state is going forwards
    if (app_state == GO_STRAIGHT) {
        //continue forward if no line detected
        if (world -> line_check() == OFF) {
            robot -> drive_forward(60);
        //there is a line, set an action to go backwards
        } else {
            robot -> brake();
            thymer -> set_action_timer(50);
            app_state = GO_BACKWARDS;
        }
    //if the current state is go backwards
    } else {
        //drive backwards
        robot -> drive_custom(45, 120, 0, 0);
    }
    return 0;
}

//drive forward if we see someone in front of us
int algorithms :: forward_safe() {
    //if the robot is close, drive forward fast
    if (world -> enemy_pos() == CLOSE_MID) {
        robot -> drive_forward(125);
    //if the robot is a little further, drive forward slower
    } else if (world -> enemy_pos() == FRONT) {
        robot -> drive_forward(80);
    //if we don't see the robot, brake and do nothing
    } else if (world -> enemy_pos() == CLOSE_MID_LEFT || world -> enemy_pos() == CLOSE_MID_RIGHT) {
        robot -> drive_forward(60);
    } else {
        robot -> brake();
    }
    return 0;
}
//returns 1 if the enemy is seen and not in front (we need to turn), 0 otherwise
int algorithms :: turn_towards() {
    
    if(world -> enemy_pos() == FRONT_LEFT) {
        //turn left a little slower
        robot -> turn_left(25);
        return 1;
    } else if (world -> enemy_pos() == LEFT) {
        //turn left
        robot -> turn_left(90);
        return 1;
    } else if (world -> enemy_pos() == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(25);
        return 1;
    } else if (world -> enemy_pos() == RIGHT) {
        //turn right
        robot -> turn_right(90);
        return 1;
    }
    return 0;
}

void algorithms :: seek_drive(enum enemy_states) {
    return;
}

int algorithms :: dodge() {
    if (world -> enemy_pos() == LEFT) {
        robot -> drive_custom(50, 150, true, true);
        return 1;
    } else if (world -> enemy_pos() == RIGHT) {
        robot -> drive_custom(150, 50, true, true);
        return 1;
    }
    return 0;
}