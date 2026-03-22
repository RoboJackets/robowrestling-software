#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"

int multiplier = 1;

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
        attack_timer -> set_action_timer(50);
    } else if (attack_timer -> check_action_time()){
        robot -> turn_left(120);
    }
}

void algorithms :: draw_seek() {
    if (enemyPosition != UNKNOWN) {
        seek();
    } else {
        draw_circle();
    }
}

void algorithms :: seek() {
    if (turn_towards() == 0) {
        attack_forward();
    } else {
        multiplier = 1;
    }
}

void algorithms :: test() {
    robot -> brake();
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
            robot -> drive_forward(100);
        //there is a line, set an action to go backwards
        } else {
            states.attack = A_BLIND;
            robot -> brake();
            draw_timer -> set_action_timer(200);
            states.circle = D_GO_BACKWARDS;
        }
    //if the current state is go backwards
    } else if (states.circle == D_GO_BACKWARDS) {
        robot -> drive_backward(150);
    } else {
        robot -> turn_left(100);
    }
    return 0;
}

//drive forward if we see someone in front of us
// assume that we have already been confirmed to see
int algorithms :: attack_forward() {
    enemy_states enemy = enemyPosition;
    if (enemy == UNKNOWN) {
        draw_circle();
        return 1;
    }
    if (states.attack == A_LOOKING && attack_timer -> check_action_time()) {
        states.attack = A_SEE;
    }
    if (states.attack == A_LOOKING || states.circle != D_GO_STRAIGHT) {
        draw_circle();
        return 1;
    }
    if (states.attack == A_SEE) {
        //if the robot is close, drive forward fast
        if (enemy == CLOSE_MID) {
            robot -> drive_forward(std::min(200 * multiplier, 255));
            multiplier += 5;
            return 1;
        //if the robot is a little further, drive forward slower
        } else if (enemy == FRONT) {
            robot -> drive_forward(std::min(150 * multiplier, 255));
            multiplier += 5;
            return 1;
        //if we don't see the robot, brake and do nothing
        } else if (enemy == CLOSE_MID) {
            robot -> drive_forward(std::min(250 * multiplier, 255));
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_LEFT) {
            robot -> drive_custom(std::min(200 * multiplier, 255), std::min(120 * multiplier, 255), 1, 1);
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_RIGHT) {
            robot -> drive_custom(std::min(200 * multiplier, 255), std::min(100 * multiplier, 255), 1, 1);
            multiplier += 5;
            return 1;
        } else {
            multiplier = 1;
            robot -> brake();
            states.swerve = S_UNKNOWN;
            return 0;
        }
    } else {
        attack_timer -> set_action_timer(500);
        states.attack = A_LOOKING;
        draw_circle();
        return 1;
    }
}
//returns 0 if we should proceed to attack_forward, returns 1 otherwise
int algorithms :: turn_towards() {
    enemy_states enemy = enemyPosition;
    if(enemy == FRONT_LEFT) {
        //turn left a little slower
        robot -> turn_left(100);
        return 1;
    } else if (enemy == LEFT) {
        //turn left
        robot -> turn_left(120);
        return 1;
    } else if (enemy == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(100);
        return 1;
    } else if (enemy == RIGHT) {
        //turn right
        robot -> turn_right(120);
        return 1;
    } else {
        return 0;
    }
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
            robot -> drive_forward(std::min(200 * multiplier, 255));
            multiplier += 5;
            return 1;
        //if the robot is a little further, drive forward slower
        } else if (enemy == FRONT) {
            robot -> drive_forward(std::min(150 * multiplier, 255));
            multiplier += 5;
            return 1;
        //if we don't see the robot, brake and do nothing
        } else if (enemy == CLOSE_MID) {
            robot -> drive_forward(std::min(250 * multiplier, 255));
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_LEFT) {
            robot -> drive_custom(std::min(200 * multiplier, 255), std::min(120 * multiplier, 255), 1, 1);
            multiplier += 5;
            return 1;
        } else if (enemy == CLOSE_MID_RIGHT) {
            robot -> drive_custom(std::min(200 * multiplier, 255), std::min(100 * multiplier, 255), 1, 1);
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
        robot -> turn_left(140);
        return 1;
    } else if (enemy == LEFT) {
        //turn left
        robot -> turn_left(170);
        return 1;
    } else if (enemy == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(140);
        return 1;
    } else if (enemy == RIGHT) {
        //turn right
        robot -> turn_right(170);
        return 1;
    } else {
        return 0;
    }
}