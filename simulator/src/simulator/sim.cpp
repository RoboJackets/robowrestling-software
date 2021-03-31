#include <simulator/sim.h>

#include <iostream>

void draw_field() {
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color(255, 0, 0));
    background.setPosition(0, 0);
    window_->draw(background);
    sf::CircleShape dohyo; //create the circle that represents the dohyo. Input is radius
    dohyo.setRadius(75.f);
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(2.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-75, (WINDOW_HEIGHT/2)-75);
    window_->draw(dohyo);
    sf::RectangleShape start_line1(sf::Vector2f(5, 50));
    start_line1.setFillColor(sf::Color(255, 69, 0));
    start_line1.setPosition(WINDOW_WIDTH/2 - 20, WINDOW_HEIGHT/2 - 25);
    window_->draw(start_line1);
    sf::RectangleShape start_line2(sf::Vector2f(5, 50));
    start_line2.setFillColor(sf::Color(255, 69, 0));
    start_line2.setPosition(WINDOW_WIDTH/2 + 20, WINDOW_HEIGHT/2 - 25);
    window_->draw(start_line2);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::RectangleShape rectangle(sf::Vector2f(robot->width_, robot->length_));
    rectangle.setFillColor(sf::Color(50, 50, 50));
    double shift_magnitude = sqrt(pow(robot->width_/2, 2) + pow(robot->length_/2, 2));
    double homogenous_x = robot->x_pos_ + shift_magnitude*cos(robot->angle_ - .75 * M_PI);
    double homogenous_y = WINDOW_HEIGHT - robot->y_pos_ + shift_magnitude*sin(robot->angle_ - .75 * M_PI);
    rectangle.setPosition(homogenous_x, homogenous_y);
    rectangle.setRotation(robot->angle_*180/M_PI);
    window_->draw(rectangle);
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
        r2_a = r2_a * M_PI;
        robot1_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-r1_x, (WINDOW_HEIGHT/2)-r1_y, r1_a);
        robot2_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)+r2_x, (WINDOW_HEIGHT/2)+r2_y, M_PI+r2_a);
    } else {
        robot1_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-25, WINDOW_HEIGHT/2-25, M_PI/4);
        robot2_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2), WINDOW_HEIGHT/2+25, M_PI);
    }
	
    BasicRobotHandler test_handler = BasicRobotHandler(robot1_, robot2_);
    physics_updater_ = std::make_shared<RobotPhysicsUpdater>();
    
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
    window_->clear(sf::Color::White); // clear the window with white color

    STRATEGY_1 r1_drive = STRATEGY_1();
    STRATEGY_2 r2_drive = STRATEGY_2();
    BasicRobotHandler r1_handler = BasicRobotHandler(robot1_, robot2_);
    BasicRobotHandler r2_handler = BasicRobotHandler(robot2_, robot1_);
    SensorData r1_data;
    SensorData r2_data;

    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    int i = 0;
	while (window_->isOpen()) {
        if (i < 5) {
            auto dummy_vector = std::vector<double>();

            r1_data = r1_handler.read(.01);
            r2_data = r2_handler.read(.01);

            physics_updater_->update(robot1_, r1_drive.next_action(r1_data), robot2_, r2_drive.next_action(r2_data), .01);
            auto readings = test_handler.read(.01);
            
            // std::cout << robot1->x_pos << ", " << robot1->y_pos << std::endl;
            // std::cout << robot2->x_pos << ", " << robot2->y_pos << std::endl;
            // i++;
        }
		update();
	}
	return 0;
}
