#include <simulator/sim.h>

#include <iostream>

void draw_field() {
    
    sf::CircleShape dohyo(150.f); //create the circle that represents the dohyo. Input is radius
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(10.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-150, (WINDOW_HEIGHT/2)-150);
    window_->draw(dohyo);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::Sprite sprite(robot_texture);
    sprite.setScale(robot->width_/50.0, robot->length_/50.0);
    double shift_magnitude = sqrt(pow(robot->width_/2, 2) + pow(robot->length_/2, 2));
    double homogenous_x = robot->x_pos_ + shift_magnitude*cos(robot->angle_ - .75 * M_PI);
    double homogenous_y = robot->y_pos_ + shift_magnitude*sin(robot->angle_ - .75 * M_PI);
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
    // window->clear();

    // need to redraw things
    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    window_->display();
}

int main(int argc, char *argv[]) {
    robot_texture.loadFromFile("../res/robot_sprite.png");
	/* code */
    if (argc == 7) {
        std::istringstream iss(std::string(argv[1])+" "+std::string(argv[2])+" "+std::string(argv[3])+" "+std::string(argv[4])+" "+std::string(argv[5])+" "+std::string(argv[6]));
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
        r1_a = r2_a * M_PI;
        robot1_ = std::make_shared<BasicRobot>(r1_x, r1_y, r1_a);
        robot2_ = std::make_shared<BasicRobot>(r2_x, r2_y, r2_a);
    } else {
        robot1_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-25, WINDOW_HEIGHT/2-25, M_PI/4);
        robot2_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2), WINDOW_HEIGHT/2+25, M_PI);
    }
	
    BasicRobotHandler test_handler = BasicRobotHandler(robot1_);
    physics_updater_ = std::make_shared<RobotPhysicsUpdater>();
    
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
    window_->clear(sf::Color::White); // clear the window with white color


    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    int i = 0;
	while (window_->isOpen()) {
        if (i < 5) {
            physics_updater_->move_robot(robot1_, 10, 5, 1); // spin my head right round, right round 
            physics_updater_->move_robot(robot2_, 10, 5, 1);
            auto dummy_vector = std::vector<double>();
            std::vector<int> r1_drive = {20, 60};
            std::cout << r1_drive[0] << ", " << r1_drive[1] << std::endl;
            physics_updater_->update(robot1_, r1_drive, robot2_, {0, 0}, .01);
            auto readings = test_handler.read(.01, robot2_);
            // std::cout << readings[0] << ", " << readings[1] << ", " << readings[2] << ", " << readings[3] << std::endl;
            // std::cout << robot1->x_pos << ", " << robot1->y_pos << std::endl;
            // std::cout << robot2->x_pos << ", " << robot2->y_pos << std::endl;
            // i++;
        }
		update();
	}
	return 0;
}
