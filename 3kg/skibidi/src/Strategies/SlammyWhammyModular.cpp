#include "Strategies/SlammyWhammyModular.hpp"

SlammyWhammyModular::SlammyWhammyModular() {}

void SlammyWhammyModular::make_decision(State *state) {
    /*
     * if (current_state == 0) {
     *     bool result = seek.make_decision(state);  // enum return?
     *     if (result) {
     *         current_state = 1;
     *         charge.make_decision(state);
     *     }
     * } else if (current_state == 1) {
     *     bool result = charge.make_decision(state);
     *     if (result) {
     *         current_state = 0;
     *         seek.make_decision(state);
     *     }
     * }
     */
}
