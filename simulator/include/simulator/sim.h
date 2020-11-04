#ifndef sim_h
#define sim_h

#include <simulator/robot.h>
#include <simulator/basicrobot.h>
#include <simulator/physics/robotphysicsupdater.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int radius_; //radius of the dohyo

std::shared_ptr<Robot> robot1_; //robot object that stores information about a robot
std::shared_ptr<Robot> robot2_; //see above

std::shared_ptr<sf::RenderWindow> window_;

std::shared_ptr<RobotPhysicsUpdater> physics_updater_;

void update(); //performs one update of the game state

void draw_field(); //draws the field

void draw_robot(std::shared_ptr<Robot> robot); //draws the robots

int main(); //main method that has the game loop
#endif