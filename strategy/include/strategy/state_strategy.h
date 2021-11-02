
#include <strategy/strategy.h>

class StateStrategy: public Strategy {
    public:
        enum State {
            SEARCH,
            TURN_LEFT,
            TURN_RIGHT,
            FORWARD 
        };

        StateStrategy();
        std::vector<int> next_action(SensorData input);
        void update_state(SensorData input);

        State state_;
};
