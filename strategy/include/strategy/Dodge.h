#ifndef Dodge_h // RENAME EVERY REFERENCE TO STRATEGY NAME
#define Dodge_h
#include <strategy/strategy.h> // Don't Change This Include

// stub class for a new strategy
// every new strategy we create must include strategy_h so since we call upon standardized methods
// in sim to execute these strategies.
class Dodge {
public:
  // Create and initialize data needed for the strategy
  Dodge();

  // Returns vector of size 2 containing ints [-100, 100] to indicate left and right motor output % respectively
  std::vector<int> next_action(SensorData input);

  // States of robot action
  enum State {
    IDLE,
    APPROACH,
    TURN_RIGHT,
    TURN_LEFT,
    //Added
    FORWARD,
    RIGHT,
    LEFT,
    SNEAKING
  };
  State state;

  // Returns the next state
  State update_state(SensorData input);
  
};

#endif
