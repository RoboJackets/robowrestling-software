#include <simulator/sim.h>

#include <iostream>

void draw_field() {
    
    sf::CircleShape dohyo(150.f); //create the circle that represents the dohyo. Input is radius
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(10.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-150, (WINDOW_HEIGHT/2)-150);
    window->draw(dohyo);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::RectangleShape rectangle(sf::Vector2f(robot->width, robot->length));
    rectangle.setFillColor(sf::Color(50, 50, 50));
    double shift_magnitude = sqrt(pow(robot->width/2, 2) + pow(robot->length/2, 2));
    double homogenous_x = robot->x_pos + shift_magnitude*cos(robot->angle - .75 * M_PI);
    double homogenous_y = robot->y_pos + shift_magnitude*sin(robot->angle - .75 * M_PI);
    rectangle.setPosition(homogenous_x, homogenous_y);
    rectangle.setRotation(robot->angle*180/M_PI + 90);
    window->draw(rectangle);
}	

void update() {
	sf::Event event;
    window->clear(sf::Color::White); // clear the window with white color
    while (window->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window->close();
        } 
    }
    // window->clear();

    // need to redraw things
    draw_field();
    draw_robot(robot1);
    draw_robot(robot2);
    window->display();
}

int main() {
	/* code */
	robot1 = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-65, WINDOW_HEIGHT/2, 0);
	robot2 = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)+65, WINDOW_HEIGHT/2, M_PI);
    physics_updater = std::make_shared<RobotPhysicsUpdater>();

    DistanceSensor* test_distance_sensor = new DistanceSensor(robot1, 0, 0, 0, M_PI/16, 200);
    std::cout << robot1->x_pos << " " <<robot1->y_pos << std::endl;

    std::cout << robot1->x_pos+test_distance_sensor->_d_x << " " <<robot1->y_pos+test_distance_sensor -> _d_y << std::endl;
    test_distance_sensor->read(robot2);

    // distance_sensor_vec.push_back(test_distance_sensor);
    
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
    window->clear(sf::Color::White); // clear the window with white color


    draw_field();
    draw_robot(robot1);
    draw_robot(robot2);
    int i = 0;
	while (window->isOpen()) {
        if (i < 5) {
            // physics_updater->move_robot(robot1, 100, 99, 1);
            // physics_updater->move_robot(robot2, 100, 99, 1);
            // std::cout << robot1->x_pos << ", " << robot1->y_pos << std::endl;
            // std::cout << robot2->x_pos << ", " << robot2->y_pos << std::endl;
            // i++;
        }
		update();
	}
	return 0;
}
