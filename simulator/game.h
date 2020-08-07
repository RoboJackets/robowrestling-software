#ifndef game_h
#define game_h

#include "robot.h"
#include "basicrobot.h"
#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int radius; //radius of the dohyo

std::unique_ptr<Robot> robot1; //robot object that stores information about a robot
std::unique_ptr<Robot> robot2; //see above

std::unique_ptr<sf::RectangleShape> robot_rectangle1;
std::unique_ptr<sf::RectangleShape> robot_rectangle2;

std::unique_ptr<sf::RenderWindow> window;

void update(); //performs one update of the game state

void initialize(); //initialize with 2 robots

int main(); //main method that has the game loop
#endif