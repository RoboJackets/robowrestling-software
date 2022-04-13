#include <simulator/sim.h>

#include <iostream>
#include <string>

#include <chrono>
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

void draw_field() {
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)); //make a rectangle to add background color
    background.setFillColor(sf::Color(141, 158, 196));
    background.setPosition(0, 0);
    window_->draw(background);
    sf::CircleShape dohyo; //create the circle that represents the dohyo. Input is radius
    dohyo.setRadius(vis_scale*75.f);
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(vis_scale*2.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-vis_scale*75, (WINDOW_HEIGHT/2)-vis_scale*75);
    window_->draw(dohyo);
    sf::RectangleShape start_line1(sf::Vector2f(vis_scale*2, vis_scale*20));
    start_line1.setFillColor(sf::Color(255, 69, 0));
    start_line1.setPosition(WINDOW_WIDTH/2 - vis_scale*10, WINDOW_HEIGHT/2 - vis_scale*10);
    window_->draw(start_line1);
    sf::RectangleShape start_line2(sf::Vector2f(vis_scale*2, vis_scale*20));
    start_line2.setFillColor(sf::Color(255, 69, 0));
    start_line2.setPosition(WINDOW_WIDTH/2 + vis_scale*10, WINDOW_HEIGHT/2 - vis_scale*10);
    window_->draw(start_line2);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::Sprite sprite(robot_texture);
    sprite.setScale(vis_scale*robot->width_/50.0, vis_scale*robot->length_/50.0);
    double shift_magnitude = vis_scale*sqrt(pow(robot->width_/2, 2) + pow(robot->length_/2, 2));
    double homogenous_x = vis_scale*(robot->x_pos_ - WINDOW_WIDTH/2) + WINDOW_WIDTH/2 + shift_magnitude*cos(robot->angle_ - .75 * M_PI);
    double homogenous_y = vis_scale*(robot->y_pos_ - WINDOW_HEIGHT/2) + WINDOW_HEIGHT/2 + shift_magnitude*sin(robot->angle_ - .75 * M_PI);
    sprite.setPosition(homogenous_x, homogenous_y);
    sprite.setRotation(robot->angle_*180/M_PI);
    window_->draw(sprite);
}	

void update() {
	sf::Event event;
    window_->clear(sf::Color::White); // clear the window with white color
    while (window_->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window_->close();
        } 
    }

    // need to redraw things
    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    window_->display();
}

int main(int argc, char *argv[]) { // ./sim.sw (r1 x left of 0) (r1 y up of 0) (r1 angle in rad cw) (r2 x right of 0) (r2 y down of 0) (r2 angle in rad cw) (duration for sim: 0 = realtime elapsed)
    robot_texture.loadFromFile("simulator/res/robot_sprite.png");
    if (argc == 8) {
        //stores string inputs from terminal and outputs while casting
        std::istringstream iss(std::string(argv[1])+" "+std::string(argv[2])+" "+std::string(argv[3])+" "+std::string(argv[4])+" "+std::string(argv[5])+" "+std::string(argv[6])+" "+std::string(argv[7]));
        double r1_x = 0.0;
        iss >> r1_x;
        double r1_y = 0.0;
        iss >> r1_y;
        double r1_a = 0.0;
        iss >> r1_a;
        r1_a = r1_a * M_PI;
        double r2_x = 0.0;
        iss >> r2_x;
        double r2_y = 0.0;
        iss >> r2_y;
        double r2_a = 0.0;
        iss >> r2_a;
        r2_a = r2_a * M_PI;
        iss >> sim_duration;
        robot1_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-r1_x, (WINDOW_HEIGHT/2)-r1_y, r1_a);
        robot2_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)+r2_x, (WINDOW_HEIGHT/2)+r2_y, M_PI+r2_a);
    } else {
        sim_duration = 0.01;
        robot1_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-25, WINDOW_HEIGHT/2-25, M_PI/4);
        robot2_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2), WINDOW_HEIGHT/2+25, M_PI);
    }

    
    physics_updater_ = std::make_shared<RobotPhysicsUpdater>(); //Default RobotPhysicsUpdater
    
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
    window_->clear(sf::Color::White); // clear the window with white color

    OPENING_1 r1_opening = OPENING_1();
    OPENING_2 r2_opening = OPENING_2();
    STRATEGY_1 r1_drive = STRATEGY_1();
    STRATEGY_2 r2_drive = STRATEGY_2();
    BrodyRobotHandler r1_handler = BrodyRobotHandler(robot1_, robot2_);
    BrodyRobotHandler r2_handler = BrodyRobotHandler(robot2_, robot1_);

    SensorData r1_data;
    SensorData r2_data;
    std::vector<int> r1_action;
    std::vector<int> r2_action;

    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);

    double elapsed_time;
    auto start_time = timeNow();
    auto past_time = timeNow();


    // sim_duration: how long to run simulator for. Otherwise use real time.
    // Opening code goes somewhere as the first action in a while loop. Does not work in simulated time cases
    if (sim_duration == 0) {
        while (window_->isOpen() && duration(timeNow() - start_time) <= 60000000000) {

            elapsed_time = duration(timeNow() - past_time) / 1000000000.0;

            if (elapsed_time > 0) {
                past_time = timeNow();

                r1_data = r1_handler.read(elapsed_time);
                r2_data = r2_handler.read(elapsed_time);

                if (r1_opening.done) {
                    r1_action = r1_drive.next_action(r1_data);
                } else {
                    r1_action = r1_opening.execute(r1_data);
                }
                if (r2_opening.done) {
                    r2_action = r2_drive.next_action(r2_data);
                } else {
                    r2_action = r2_opening.execute(r2_data);
                }

                physics_updater_->update(robot1_, r1_action, robot2_, r2_action, elapsed_time);
            }

            update();
        }

        std::cout << duration(timeNow() - start_time) / 1000000000 << std::endl;
    } else {
        while (window_->isOpen()) {

            r1_data = r1_handler.read(sim_duration);
            r2_data = r2_handler.read(sim_duration);

            physics_updater_->update(robot1_, r1_drive.next_action(r1_data), robot2_, r2_drive.next_action(r2_data), sim_duration);

            elapsed_total += sim_duration;

            update();
        }

        std::cout << "Match Time: " << elapsed_total << std::endl;
    }
	return 0;
}


