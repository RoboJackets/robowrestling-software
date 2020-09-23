#ifndef sim_h
#define sim_h

#include "robot.h"
#include "basicrobot.h"
#include "robotphysicsupdater.h"
#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int radius; //radius of the dohyo

Robot* robot1; //robot object that stores information about a robot
Robot* robot2; //see above

sf::RenderWindow* window;

RobotPhysicsUpdater* physics_updater;

void update(); //performs one update of the game state

void draw_field(); //draws the field

void draw_robot(Robot* robot); //draws the robots

int main(); //main method that has the game loop
#endif