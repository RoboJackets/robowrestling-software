#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"


algorithms :: algorithms(robot_actions *robot, world_state *world, timer* thymer) {
    this -> robot = robot;
    this -> world = world;
    this -> thymer = thymer;
    states.circle = D_GO_STRAIGHT;
    states.swerve = S_UNKNOWN;
}

int algorithms :: draw_circle() {
    //if the timer went off (action has completed)
    if (states.circle == D_GO_BACKWARDS && thymer -> check_action_time()) {
        states.circle = D_GO_STRAIGHT;
        robot -> brake();
        return 0;
    }
    //if a timer isn't currently going off
    //if the current state is going forwards
    if (states.circle == D_GO_STRAIGHT) {
        //continue forward if no line detected
        if (world -> line_check() == OFF) {
            robot -> drive_forward(50);
        //there is a line, set an action to go backwards
        } else {
            robot -> brake();
            thymer -> set_action_timer(30);
            states.circle = D_GO_BACKWARDS;
        }
    //if the current state is go backwards
    } else {
        //drive backwards
        robot -> drive_custom(45, 120, 0, 0);
    }
    return 0;
}

//drive forward if we see someone in front of us
int algorithms :: attack_forward() {
    //if the robot is close, drive forward fast
    if (world -> enemy_pos() == CLOSE_MID) {
        robot -> drive_forward(250);
    //if the robot is a little further, drive forward slower
    } else if (world -> enemy_pos() == FRONT) {
        robot -> drive_forward(200);
    //if we don't see the robot, brake and do nothing
    } else if (world -> enemy_pos() == CLOSE_MID_LEFT || world -> enemy_pos() == CLOSE_MID_RIGHT) {
        robot -> drive_forward(250);
    } else {
        robot -> brake();
        states.swerve = S_UNKNOWN;
    }
    return 0;
}
//returns 1 if the enemy is seen and not in front (we need to turn), 0 otherwise
int algorithms :: turn_towards() {
    
    if(world -> enemy_pos() == FRONT_LEFT) {
        //turn left a little slower
        robot -> turn_left(120);
        return 1;
    } else if (world -> enemy_pos() == LEFT) {
        //turn left
        robot -> turn_left(140);
        return 1;
    } else if (world -> enemy_pos() == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(120);
        return 1;
    } else if (world -> enemy_pos() == RIGHT) {
        //turn right
        robot -> turn_right(140);
        return 1;
    }
    return 0;
}

void algorithms :: seek_drive() {
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

// return 0 if we should go forward, return -1 if we don't see the robot
int algorithms :: swerve() {
    if (states.swerve == S_GO_STRAIGHT && thymer -> check_action_time() == 0) {
        robot -> drive_forward(50);
        return 1;
    }
    if (states.swerve == S_ATTACK) {
        return 0;
    } else if (states.swerve == S_UNKNOWN) {
        if (world -> enemy_pos() == FRONT || world -> enemy_pos() == FRONT_LEFT || world -> enemy_pos() == FRONT_RIGHT) {
            states.swerve = S_TURN_AWAY;
            thymer -> set_action_timer(400);
            robot -> brake();
            return 1;
        } else if (world -> enemy_pos() == RIGHT || world -> enemy_pos() == LEFT) {
            states.swerve = S_ATTACK;
            return 0;
        }
        robot -> brake();
        return -1;
    } else if (thymer -> check_action_time()) {
        if (world -> enemy_pos() != UNKNOWN) {
            states.swerve = S_ATTACK;
            return 0;
        } else {
            states.swerve = S_UNKNOWN;
            return -1;
        }
    } else if (states.swerve == S_TURN_AWAY) {
        if (world -> enemy_pos() == RIGHT) {
            states.swerve = S_GO_STRAIGHT;
            robot -> brake();
            thymer -> set_action_timer(40);
            return 1;
        }
        robot -> turn_left(50);
        return 1;
    } else if (states.swerve == S_GO_STRAIGHT) {
        if (world -> enemy_pos() == UNKNOWN) {
            robot -> brake();
            thymer -> set_action_timer(400);
            states.swerve = S_TURN_BACK;
            return 1;
        }
        robot -> drive_forward(50);
        return 1;
    } else if (states.swerve == S_TURN_BACK) {
        if (world -> enemy_pos() == FRONT || world -> enemy_pos() == CLOSE_MID_LEFT
            || world -> enemy_pos() == CLOSE_MID_RIGHT || world -> enemy_pos() == CLOSE_MID) {
            states.swerve = S_ATTACK;
            return 0;
        }
        robot -> turn_right(50);
        return 1;
    }
    return 0;
}

void algorithms :: brake() {
    robot -> brake();
}