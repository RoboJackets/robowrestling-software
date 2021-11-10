# robowrestling-software

## Installation Guide

### C++ Setup

1. For Mac
    1. Install XCode

1. For Windows
    1. Install Linux Terminal: [Guide](https://www.windowscentral.com/install-windows-subsystem-linux-windows-10)
    2. Use your preferred code editor
    3. Follow the **For Linux** setup
    
1. For Linux
    1. Open a terminal and run the following commands:

        ```
        <sudo apt-get update>
        <sudo apt-get install c++>
        ```
    
    2. Use your preferred code editor
  
### Git/Github Setup
  
1. Linking Accounts
    1. Sign in to your Robojackets Account: [my.robojackets.org](my.robotjackets.org)
    2. Go to profile and add accounts for both github and google
    
2. Update Identity: [Guide](https://docs.github.com/en/get-started/quickstart/set-up-git)
    1. Follow the **Setting Up Git** section

3. Generate a PAT if needed (Make sure to not lose): 
    [Guide](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)

4. Download the Github Desktop App (Optional): [Download](https://desktop.github.com/)

5. Clone the robowrestling-software repository: [repo](https://github.com/RoboJackets/robowrestling-software)

### Dependencies Installation

1. For Linux/Windows
    1. Open a terminal and run the following commands:
    
        ```
        <sudo apt-get update>
        <sudo apt-get install cmake libsfml-dev>
        ```
    
    2. (Windows Only) Install Xming: [Download](https://sourceforge.net/projects/xming/)

2. For Mac
    1. Install XCode extensions for Cmake and SFML

### Arduino IDE Setup

1. Install Arduino IDE: [Download](https://www.arduino.cc/en/software)

2. Install Teensyduino: [Download](https://www.pjrc.com/teensy/td_download.html)

## Running the Simulator

1. For Linux
    1. Open a terminal and locate the head of the repo: 
    
        `user:~/.../robowrestling-software/`
    
    2. Build Cmake (First Time Only): 
    
        ```
        cmake .
        ```
    
    3. Compile the Source Code:
    
        ```
        make
        ```
    
    4. (Windows Only) Connect to Xming Display (Run each time a terminal is opened):
    
        ```
        export DISPLAY=:0
        ```
    
    5. Run the Simulator:
    
        ```
        ./simulator/src/sim.sw 50 0 0 50 0 0 0
        ```
    
2. For Mac
    1. **TODO**

### Changing Configuration

## Strategies

### Making a new Strategy

1. Develop a state machine diagram to reference. Example:

    ![state_strategy](/strategy/diagrams/state_strategy.png)
    
2. Create a new header and cpp file in the `/strategy/include/` and `/strategy/src/` folders respectively

3. Use the following templates:
    1. Header:
    
        ``` 
        #ifndef strategy_name_h // RENAME EVERY REFERENCE TO STRATEGY NAME
        #define strategy_name_h
        #include <strategy/strategy.h> // Don't Change This Include

        // stub class for a new strategy
        // every new strategy we create must include strategy_h so since we call upon standardized methods 
        // in sim to execute these strategies.
        class StrategyName {
            public:
                // Create and initialize data needed for the strategy
                StrategyName();

                // Returns vector of size 2 containing ints [-100, 100] to indicate left and right motor output % respectively
                std::vector<int> next_action(SensorData input);

                // Returns the next state
                State update_state(SensorData input);

                // States of robot action
                enum State {
                    IDLE,
                    APPROACH,
                    TURN_RIGHT,
                    TURN_LEFT
                } state;
        };

        #endif
        ```
        
    2. Cpp:
    
        ``` 
        #include <strategy/strategy_name.h>
        #include <iostream>

        // Create and initialize data needed for the strategy
        StrategyName::StrategyName() {
            state = IDLE;
        }

        // Returns the intended action in the format {Left Motor Power %, Right Motor Power %}
        std::vector<int> StrategyName::next_action(SensorData input) {
            int output[] = {0, 0};
            state = update_state(input);

            switch (state) {
            case IDLE:
                output[0] = 0;
                output[1] = 0;
                break;
            case APPROACH:
                output[0] = 80;
                output[1] = 80;
                break;
            case TURN_LEFT:
                output[0] = -50;
                output[1] = 50;
                break;
            case TURN_RIGHT:
                output[0] = 50;
                output[1] = -50;
                break;
            default:
                break;
            }

            return std::vector<int>(output[0], output[1]);
        }

        // Checks sensors and returns the appropriate state of action
        StrategyName::State StrategyName::update_state(SensorData input) {
            if () {
                return APPROACH;
            } else if ()
                return TURN_RIGHT;
            } else if () {
                return TURN_LEFT;
            } else {
                return IDLE;
            }
        }
        ```
    
4. Add the Strategy to the build path
    1. Locate `/strategy/CMakeLists.txt`
    2. Add the Strategy to the list `<add_library(Strategies src/**STRATEGY_NAME_HERE**.cpp ...`
    
5. Select the Strategy to run on a compatible Robot
    1. Locate `/simulator/include/simulator/sim.h`
    2. Include the Strategy for Selection
    
        ```
        #include <strategy/**STRATEGY_NAME_HERE**.h>
        ```
        
    3. Change a Robot's selection `<#define STRATEGY_1 **STRATEGY_NAME_HERE**>`
