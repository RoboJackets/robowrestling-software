#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"

algorithms :: algorithms(robot_actions *robot, world_state *world, timer* thymer) {
    this -> robot = robot;
    this -> world = world;
    this -> thymer = thymer;
    app_state = GO_STRAIGHT;
    forward_speed = 40;
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
    //if the timer started
    if (thymer -> check_action_time()) {
        //if the state is to go backwards
        if (app_state == GO_BACKWARDS) {
            app_state = TURN;
            thymer -> set_action_timer(50);
            robot -> brake();
            return 0;
        } else if (app_state == TURN) {
            app_state = GO_STRAIGHT;
            robot -> brake();
            return 0;
        }
    }
<<<<<<< HEAD
    
=======
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
    //if there's no timer
    }
>>>>>>> fa014884d4e65b04004f5f3eb82424e54448f173
    if (app_state == GO_STRAIGHT) {
        if (world -> line_check() == OFF) {
            robot -> drive_forward(forward_speed);
        } else {
            robot -> brake();
            thymer -> set_action_timer(20);
            app_state = GO_BACKWARDS;
        }
    } else if (app_state == TURN) {
        if (world -> line_check() == OFF) {
            robot -> turn_right(75);
        } else {
            robot -> brake();
            thymer -> set_action_timer(35);
            app_state = GO_BACKWARDS;
        }
    } else if (app_state == GO_BACKWARDS) {
        if (!thymer -> get_timer_state()) {
            thymer -> set_action_timer(10);
        } else {
            robot -> drive_backward(90);
        }
    }
    return 0;
}

int algorithms :: forward_safe() {
    if (world -> enemy_pos() == CLOSE_MID_LEFT || world -> enemy_pos() == CLOSE_MID_RIGHT || world -> enemy_pos() == CLOSE_MID) {
        robot -> drive_forward(125);
    } else if (world -> enemy_pos() == FRONT) {
        robot -> drive_forward(80);
    } else {
        robot -> brake();
    }
    return 0;
}
//returns 1 if the enemy is seen and not in front (we need to turn), 0 otherwise
int algorithms :: turn_towards() {
    //if the enemy is to the left
    if (world -> enemy_pos() == LEFT) {
        //turn left
        robot -> turn_left(100);
        return 1;
    //if the enemy is to the front and left
    } else if(world -> enemy_pos() == FRONT_LEFT) {
        //turn left a little slower
        robot -> turn_left(50);
        return 1;
    //if the enemy is to the right
    } else if (world -> enemy_pos() == RIGHT) {
        //turn right
        robot -> turn_right(100);
        return 1;
    //if the enemy is to the front and right
    } else if (world -> enemy_pos() == FRONT_RIGHT) {
        //turn right a little slower
        robot -> turn_right(50);
        return 1;
    }
    return 0;
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