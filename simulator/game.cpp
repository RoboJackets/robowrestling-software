#include "game.h"



void initialize(Robot* robo1, Robot* robo2) {
	robot1 = robo1;
	robot2 = robo2;
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
	window.clear(sf::Color::White); // clear the window with white color
	sf::CircleShape dohyo(150.f); //create the circle that represents the dohyo
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(10.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    window.draw(dohyo);

    robot_rectangle1(sf::Vector2f(robot1->width, robot1->length));
    robot_rectangle1.setFillColor(sf::Color(50, 50, 50));
    robot_rectangle1.setPosition(robot1->x_pos, robot1->y_pos);
    window.draw(robot_rectangle1);

    robot_rectangle2(sf::Vector2f(robot2->width, robot2->length));
    robot_rectangle2.setFillColor(sf::Color(50, 50, 50));
    robot_rectangle2.setPosition(robot2->x_pos, robot2->y_pos);
    window.draw(robot_rectangle2);
}	

void update() {
	sf::Event event;
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.display();
}

int main() {
	/* code */
	initialize(new Robot((WINDOW_WIDTH/2)-65, WINDOW_HEIGHT/2, 90), new Robot((WINDOW_WIDTH/2)+65, WINDOW_HEIGHT/2, 270));
	while (window.isOpen()) {
		update();
	}
	return 0;
}