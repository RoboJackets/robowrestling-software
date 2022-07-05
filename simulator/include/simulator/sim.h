#ifndef sim_h
#define sim_h


#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>
#include <sstream>


// Gui Includes

#include <graphics/widgets/ImguiManager.h>
#include <graphics/widgets/Pane.h>
#include <graphics/widgets/FPSWidget.h>
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


#include <simulator/physics/robotphysicsupdater.h>


#define WINDOW_HEIGHT (vis_scale*720)
#define WINDOW_WIDTH (vis_scale*1280)

#define OPENING_1 TimedOpening // Edit to change Robot 1's opening. Remember to include
#define OPENING_2 NoOpening

#define STRATEGY_1 IdleStrategy // Edit to change Robot 1's strategy. Remember to include
#define STRATEGY_2 SlammyWhammy


int radius_; //radius of the dohyo
double elapsed_total;
double sim_duration;
double vis_scale = 2.5;

std::shared_ptr<Robot> robot1_; //robot object that stores information about a robot
std::shared_ptr<Robot> robot2_; //see above

std::shared_ptr<ImguiManager> _manager; 
std::shared_ptr<Pane> _leftPane; 
std::shared_ptr<Pane> _bottomPane; 
std::shared_ptr<Pane> _fpsPane; 
std::shared_ptr<sf::RenderWindow> window_;

// widgets
std::shared_ptr<FPSWidget> _fpsWidget; 

std::shared_ptr<RobotPhysicsUpdater> physics_updater_;

sf::Texture robot_texture;

void update(); //performs one update of the game state

void draw_field(); //draws the field

void draw_robot(std::shared_ptr<Robot> robot); //draws the robots

int main(int argc, char *argv[]); //main method that has the game loop
#endif
