#ifndef game_h
#define game_h

#include "robot.h"
#include "basicrobot.h"
#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int radius; //radius of the dohyo

Robot* robot1; //robot object that stores information about a robot
Robot* robot2; //see above

sf::RectangleShape robot_rectangle1;
sf::RectangleShape robot_rectangle2;

sf::RenderWindow window;

void update(); //performs one update of the game state

void initialize(Robot* robot1, Robot* robot2); //initialize with 2 robots

int main(); //main method that has the game loop
#endif