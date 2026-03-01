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

// main strategy function
// step 1:
//      swerve_timer is set in main to 300 millis
//      drive_forward at start of match until swerve timer goes off
// step 2:
//      slammy_whammy: if there is an enemy seen, calls turn_towards_no_delay, if enemy ahead, attack_forward_no_delay
//          turn_towards_no_delay: turns toward enemy if not ahead, returns 0 if enemy is straight ahead
//          attack_forward_no_delay: attacks for 100 millis if enemy is ahead
//      draw_circle: runs if slammy_whammy returns 0 (no enemy seen)
//          drives until line is seen, then backs off and turns, then coninues forward
//          seek_drive: used such that when driving forward, robot swerves left and right to try to find enemy
void algorithms :: match_strategy() {
    // update positions
    selfPosition = world -> line_check();
    enemyPosition = world -> enemy_pos();

    // at beginning of round, drive forward for a bit
    if (match_start) {
        Serial.println("match start");

        if (swerve_timer -> check_action_time()) {
            match_start = false;
        } else {
            robot -> drive_forward(max_speed);
            return;
        }
    }

    // if enemy is unseen, 
    if (slammy_whammy() == 0) {
        draw_circle();
    }
}

// returns 0 if no enemy detected, otherwise 1
// turns toward enemy if not ahead
// attacks for 100 millis if enemy is ahead
int algorithms :: slammy_whammy() {
    // no enemy detected
    if (enemyPosition == UNKNOWN) {
        return 0;
    }
    // if already facing enemy, attack
    if (turn_towards_no_delay() == 0) {
        attack_forward_no_delay();
    } else {
        // reset multiplier if no enemy
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
    // state transition for backng off and turning away from line
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

    // action during each state
    // if the current state is going straight
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
    // if the current state is go backwards
    } else if (states.circle == D_GO_BACKWARDS) {
        robot -> drive_backward(max_speed);
    // if the current state is neither, turn to find enemy
    // this should never be reached
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

// move forward while scanning left and right
// currenly only moves forward because swerve timer is not set
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


// drive forward if we see someone in front of us and return 1, otherwise return 0
// assume that we have already been confirmed to see
// multiplier increases the speed the longer we see enemy
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