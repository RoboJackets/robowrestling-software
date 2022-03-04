#ifndef sim_h
#define sim_h


#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>
#include <sstream>

// Robot Includes
#include <simulator/robots/robot.h>
#include <simulator/robots/basicrobot.h>
#include <simulator/sensors/basicrobot_handler.h>

// Opening Includes
#include <opening/timed_opening.h>
#include <opening/no_opening.h>

// Strategy Includes
#include <strategy/basic_dist.h>
#include <strategy/idle_strategy.h>
#include <strategy/sensor_strategy.h>
#include <strategy/slammywhammy.h>

#include <strategy/kevin_brody.h>
#include <strategy/antiaim.h>
#include <strategy/kevin_brody_enemy.h>
#include <strategy/search_strategy.h>
#include <strategy/Dodge.h>

#include <strategy/side_swipe.h>

#include <simulator/physics/robotphysicsupdater.h>



#define WINDOW_HEIGHT (vis_scale*200)
#define WINDOW_WIDTH (vis_scale*200)

#define OPENING_1 NoOpening // Edit to change Robot 1's opening. Remember to include
#define OPENING_2 NoOpening

#define STRATEGY_1 KevinBrodyStrategyEnemy // Edit to change Robot 1's strategy. Remember to include
#define STRATEGY_2 IdleStrategy


int radius_; //radius of the dohyo
double elapsed_total;
double sim_duration;
double vis_scale = 2.5;

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
