#include "utility/ActionSequence.hpp"

ActionSequence::ActionSequence() {
    actionList = new LinkedList<Action*>();
    isActionSequenceInitiated = false;
    isActionSequenceCompleted = false;
}

ActionSequence::ActionSequence(LinkedList<Action*> *_actionList) {
    actionList = cloneLinkedList(_actionList);
    isActionSequenceInitiated = false;
    isActionSequenceCompleted = false;
    actionList->sort(compareActions);
}

void ActionSequence::add(Action *_action) {
    actionList->add(_action);
    actionList->sort(compareActions);
}

void ActionSequence::run() {
    if (isActionSequenceCompleted) {
        return;
    }
    if (currentActionList->size() == 0 && currentAction->getActionCompleted()) {
        isActionSequenceCompleted = true;
        return;
    }
    if (!isActionSequenceInitiated) {
        isActionSequenceInitiated = true;
        currentActionList = cloneLinkedList(actionList);
        currentAction = currentActionList->shift();
        currentAction->resetAction();
    }
    if (currentAction->getActionCompleted()) {
        currentAction = currentActionList->shift();
        currentAction->resetAction();
    }
    currentAction->run();
}

void ActionSequence::resetActionSequence() {
    isActionSequenceCompleted = false;
    isActionSequenceInitiated = false;
}