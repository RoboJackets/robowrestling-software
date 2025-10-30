#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"
#include <Arduino.h>
int multiplier = 1;
int fast_turn = 512;
int fast_forward = 512;
int max_speed = 512;

algorithms :: algorithms(robot_actions *robot, world_state *world, timer* draw_timer, timer *attack_timer) {
    this -> robot = robot;
    this -> world = world;
    this -> draw_timer = draw_timer;
    this -> attack_timer = attack_timer;
    selfPosition = OFF;
    enemyPosition = UNKNOWN;
    states.circle = D_GO_STRAIGHT;
    states.swerve = S_UNKNOWN;
    states.attack = A_BLIND;
    turn_direction = 0;
}

void algorithms :: match_strategy() {
    selfPosition = world -> line_check();
    enemyPosition = world -> enemy_pos();
    // slammy_whammy();
    draw_circle();
}

void algorithms :: slammy_whammy() {
    if (enemyPosition != UNKNOWN) {
        if (turn_towards_no_delay() == 0) {
            attack_forward_no_delay();
        } else {
            multiplier = 1;
        }
        attack_timer -> set_action_timer(100);
    } else if (attack_timer -> check_action_time()) {
        if (turn_direction == 0) {
            robot -> turn_left(200);
        } else {
            robot -> turn_right(200);
        }
    }
}

int algorithms :: draw_circle() {
    //if the timer went off (action has completed)
    if (states.circle == D_GO_BACKWARDS && draw_timer -> check_action_time()) {
        states.circle = D_TURN;
        robot -> brake();
        states.attack = A_BLIND;
        draw_timer -> set_action_timer(200);
        return 0;
    } else if (states.circle == D_TURN && draw_timer -> check_action_time()) {
        states.circle = D_GO_STRAIGHT;
        robot -> brake();
        return 0;
    }
    //if a timer isn't currently going off
    //if the current state is going forwards
    if (states.circle == D_GO_STRAIGHT) {
        //continue forward if no line detected
        if (selfPosition == OFF) {
            robot -> drive_forward(60);
        //there is a line, set an action to go backwards
        } else {
            states.attack = A_BLIND;
            robot -> brake();
            draw_timer -> set_action_timer(200);
            states.circle = D_GO_BACKWARDS;
        }
    //if the current state is go backwards
    } else if (states.circle == D_GO_BACKWARDS) {
        robot -> drive_backward(80);
    } else {
        robot -> turn_left(70);
    }
    return 0;
}

void algorithms :: seek_drive() {
    robot -> drive_forward(100);
}

int algorithms :: dodge() {
    if (enemyPosition == LEFT) {
        robot -> drive_custom(75, 150, true, true);
        return 1;
    } else if (enemyPosition == RIGHT) {
        robot -> drive_custom(150, 75, true, true);
        return 1;
    }
    return 0;
}

// return 0 if we should go forward, return -1 if we don't see the robot
int algorithms :: swerve() {
    if (states.swerve == S_GO_STRAIGHT && draw_timer -> check_action_time() == 0) {
        robot -> drive_forward(100);
        return 1;
    }
    if (states.swerve == S_ATTACK) {
        return 0;
    } else if (states.swerve == S_UNKNOWN) {
        if (enemyPosition == FRONT || enemyPosition == FRONT_LEFT || enemyPosition == FRONT_RIGHT) {
            states.swerve = S_TURN_AWAY;
            draw_timer -> set_action_timer(400);
            robot -> brake();
            return 1;
        }
        robot -> brake();
        return -1;
    } else if (draw_timer -> check_action_time()) {
        if (enemyPosition != UNKNOWN) {
            states.swerve = S_ATTACK;
            return 0;
        } else {
            states.swerve = S_UNKNOWN;
            return -1;
        }
    } else if (states.swerve == S_TURN_AWAY) {
        if (enemyPosition == RIGHT) {
            states.swerve = S_GO_STRAIGHT;
            robot -> brake();
            draw_timer -> set_action_timer(40);
            return 1;
        }
        robot -> turn_left(80);
        return 1;
    } else if (states.swerve == S_GO_STRAIGHT) {
        if (enemyPosition == UNKNOWN) {
            robot -> brake();
            draw_timer -> set_action_timer(400);
            states.swerve = S_TURN_BACK;
            return 1;
        }
        robot -> drive_forward(100);
        return 1;
    } else if (states.swerve == S_TURN_BACK) {
        if (enemyPosition == FRONT || enemyPosition == CLOSE_MID_LEFT
            || enemyPosition == CLOSE_MID_RIGHT || enemyPosition == CLOSE_MID) {
            states.swerve = S_ATTACK;
            return 0;
        }
        robot -> turn_right(80);
        return 1;
    }
    return 0;
}




//drive forward if we see someone in front of us
// assume that we have already been confirmed to see
int algorithms :: attack_forward_no_delay() {
    enemy_states enemy = enemyPosition;
    //if the robot is close, drive forward fast
        //if the robot is close, drive forward fast
        if (enemy == CLOSE_MID) {
            robot -> drive_forward(std::min(200 * multiplier, max_speed));
            multiplier += 5;
            return 1;
        //if the robot is a little further, drive forward slower
        } else if (enemy == FRONT) {
            robot -> drive_forward(std::min(150 * multiplier, max_speed));
            multiplier += 5;
            return 1;
        //if we don't see the robot, brake and do nothing
        } else if (enemy == CLOSE_MID) {
            robot -> drive_forward(std::min(250 * multiplier, max_speed));
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_LEFT) {
            robot -> drive_custom(std::min(200 * multiplier, max_speed), std::min(120 * multiplier, max_speed), 1, 1);
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_RIGHT) {
            robot -> drive_custom(std::min(200 * multiplier, max_speed), std::min(100 * multiplier, max_speed), 1, 1);
            multiplier += 5;
            return 1;
        } else {
            multiplier = 1;
            robot -> brake();
            states.swerve = S_UNKNOWN;
            return 0;
        }
}
//returns 0 if we should proceed to attack_forward, returns 1 otherwise
int algorithms :: turn_towards_no_delay() {
    enemy_states enemy = enemyPosition;
    if(enemy == FRONT_LEFT) {
        //turn left a little slower
        robot -> turn_left(fast_turn * .7);
        turn_direction = 0;
        return 1;
    } else if (enemy == LEFT) {
        //turn left
        robot -> turn_left(fast_turn * .8);
        turn_direction = 0;
        return 1;
    } else if (enemy == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(fast_turn * .7);
        turn_direction = 1;
        return 1;
    } else if (enemy == RIGHT) {
        //turn right
        robot -> turn_right(fast_turn * .8);
        turn_direction = 1;
        return 1;
    } else {
        return 0;
    }
}