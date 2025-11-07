#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"
#include <Arduino.h>
int multiplier = 1;
int max_speed = 512;


algorithms :: algorithms(robot_actions *robot, world_state *world, timer* draw_timer, timer *attack_timer, timer *swerve_timer) {
    this -> robot = robot;
    this -> world = world;
    this -> draw_timer = draw_timer;
    this -> attack_timer = attack_timer;
    this -> swerve_timer = swerve_timer;
    selfPosition = OFF;
    enemyPosition = UNKNOWN;
    states.circle = D_GO_STRAIGHT;
    turn_direction = 0;
}
bool match_start = true;
void algorithms :: match_strategy() {
    selfPosition = world -> line_check();
    enemyPosition = world -> enemy_pos();
    if (match_start) {
        Serial.println("match start");
        if (swerve_timer -> check_action_time()) {
            match_start = false;
        } else {
            robot -> drive_forward(max_speed);
            return;
        }
    }
    if (slammy_whammy() == 0) {
        draw_circle();
    }
}

int algorithms :: slammy_whammy() {
    if (enemyPosition == UNKNOWN) {
        return 0;
    }
    if (turn_towards_no_delay() == 0) {
        attack_forward_no_delay();
    } else {
        multiplier = 1;
    }
    attack_timer -> set_action_timer(100);
    return 1;
}

void algorithms :: test() {
    // drive forward at constant speed
    robot -> drive_forward(100);
}

int algorithms :: draw_circle() {
    // check if the bot is currently backing off or turning after hitting a line
    if (states.circle == D_GO_BACKWARDS && draw_timer -> check_action_time()) {
        // finished backing off, start turning
        states.circle = D_TURN;
        robot -> brake();
        draw_timer -> set_action_timer(100);
        return 0;
    } else if (states.circle == D_TURN && draw_timer -> check_action_time()) {
        // finished turning, start going forwards again
        states.circle = D_GO_STRAIGHT;
        robot -> brake();
        return 0;
    }
    // state is going straight
    if (states.circle == D_GO_STRAIGHT) {
        //continue forward if no line detected
        if (selfPosition == OFF) {
            seek_drive();
        //there is a line, set an action to go backwards
        } else {
            robot -> brake();
            draw_timer -> set_action_timer(200);
            states.circle = D_GO_BACKWARDS;
        }
    //if the current state is go backwards
    } else if (states.circle == D_GO_BACKWARDS) {
        robot -> drive_backward(max_speed);
    } else {
        robot -> turn_left(max_speed);
    }
    return 0;
}

int left_inc = -2;
int right_inc = 2;
int tolerance = 90;
int base = 100;
int left_speed = base;
int right_speed = base;

void algorithms :: seek_drive() {
    if (swerve_timer -> check_action_time()) {
        robot -> drive_custom(left_speed, right_speed, true, true);
        if (millis() % 10 == 0) {
            if (abs(left_speed-base) >= tolerance) {
                left_inc *= -1;
            }
            if (abs(right_speed-base) >= tolerance) {
                right_inc *= -1;
            }
            left_speed += left_inc;
            right_speed += right_inc;
            if (left_speed == right_speed) {
                swerve_timer -> set_action_timer(500);
            }
        }
    } else {
        robot -> drive_forward(base);
    }
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
        } else if (enemy == CLOSE_MID_LEFT) {
            robot -> drive_custom(std::min(200 * multiplier, max_speed), std::min(120 * multiplier, max_speed), 1, 1);
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_RIGHT) {
            robot -> drive_custom(std::min(200 * multiplier, max_speed), std::min(100 * multiplier, max_speed), 1, 1);
            multiplier += 5;
            return 1;
        //if we don't see the robot, brake and do nothing
        } else {
            multiplier = 1;
            robot -> brake();
            return 0;
        }
}

// returns 0 if we should proceed to attack_forward, returns 1 otherwise
// changes turn direction to last seen direction
int algorithms :: turn_towards_no_delay() {
    enemy_states enemy = enemyPosition;
    if(enemy == FRONT_LEFT) {
        //turn left a little slower
        robot -> turn_left(max_speed * .7);
        turn_direction = 0;
        return 1;
    } else if (enemy == LEFT) {
        //turn left
        robot -> turn_left(max_speed * .8);
        turn_direction = 0;
        return 1;
    } else if (enemy == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(max_speed * .7);
        turn_direction = 1;
        return 1;
    } else if (enemy == RIGHT) {
        //turn right
        robot -> turn_right(max_speed * .8);
        turn_direction = 1;
        return 1;
    } else {
        return 0;
    }
}