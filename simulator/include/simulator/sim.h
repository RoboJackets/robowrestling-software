#ifndef sim_h
#define sim_h

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>
#include <sstream>

#include <simulator/robots/robot.h>
#include <simulator/robots/basicrobot.h>
#include <simulator/sensors/basicrobot_handler.h>

#include <simulator/physics/robotphysicsupdater.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int radius_; //radius of the dohyo

std::shared_ptr<Robot> robot1_; //robot object that stores information about a robot
std::shared_ptr<Robot> robot2_; //see above

std::shared_ptr<sf::RenderWindow> window_;

std::shared_ptr<RobotPhysicsUpdater> physics_updater_;

sf::Texture robot_texture;

void update(); //performs one update of the game state

void draw_field(); //draws the field

void draw_robot(std::shared_ptr<Robot> robot); //draws the robots

int main(int argc, char *argv[]); //main method that has the game loop
#endif