#ifndef sim_h
#define sim_h

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>

#include <simulator/robot.h>
#include <simulator/basicrobot.h>
#include <simulator/physics/robotphysicsupdater.h>

#include <simulator/abstract_distance_sensor.h>
#include <simulator/abstract_line_sensor.h>
#include <simulator/distance_sensor.h>


#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int radius_; //radius of the dohyo

std::shared_ptr<Robot> robot1_; //robot object that stores information about a robot
std::shared_ptr<Robot> robot2_; //see above

std::shared_ptr<sf::RenderWindow> window;
std::vector<AbstractDistanceSensor*> distance_sensor_vec;
std::vector<AbstractLineSensor*> line_sensor_vec;

std::shared_ptr<RobotPhysicsUpdater> physics_updater_;

void update(); //performs one update of the game state

void draw_field(); //draws the field

void draw_robot(std::shared_ptr<Robot> robot); //draws the robots

int main(); //main method that has the game loop
#endif