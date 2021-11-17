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
