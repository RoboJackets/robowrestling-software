#include <simulator/sim.h>


void initialize() {	
	window.reset(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window"));
	window->clear(sf::Color::White); // clear the window with white color
	sf::CircleShape dohyo(150.f); //create the circle that represents the dohyo. Input is radius
}

void draw_field() {
    
    sf::CircleShape dohyo(150.f); //create the circle that represents the dohyo. Input is radius
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(10.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-150, (WINDOW_HEIGHT/2)-150);
    window->draw(dohyo);
}

void draw_robot(Robot* robot) {
    sf::RectangleShape rectangle(sf::Vector2f(robot->width, robot->length));
    rectangle.setFillColor(sf::Color(50, 50, 50));
    rectangle.setPosition(robot->x_pos - robot->width/2, robot->y_pos - robot->length/2);
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
	robot1.reset(new BasicRobot((WINDOW_WIDTH/2)-65, WINDOW_HEIGHT/2, 90));
	robot2.reset(new BasicRobot((WINDOW_WIDTH/2)+65, WINDOW_HEIGHT/2, 270));
	initialize();
	while (window->isOpen()) {
		update();
	}
	return 0;
}
