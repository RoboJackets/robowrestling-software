#include "utility/ActionSequence.hpp"

ActionSequence::ActionSequence(bool loopSequence, bool restartSequence, int *currentTimePtr) {
    loop = loopSequence;
    restart = restartSequence;
    currentTime = currentTimePtr;
}

void ActionSequence::addAction(void *operation(), int duration) {
    
}

void ActionSequence::executeAction() {

}