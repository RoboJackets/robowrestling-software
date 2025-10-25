#ifndef ACTIONSEQUENCE_H
#define ACTIONSEQUENCE_H

#include <LinkedList.h>
#include "Action.hpp"

class ActionSequence {
    private:
        LinkedList<Action*> *actionList;
        LinkedList<Action*> *currentActionList;
        Action* currentAction;
        bool isActionSequenceInitiated;
        bool isActionSequenceCompleted;
        static int compareActions(Action* &a, Action* &b) {
            if (a->getPriority() > b->getPriority()) return -1;
            if (a->getPriority() < b->getPriority()) return 1;
            return 0;
        }
        static LinkedList<Action*> *cloneLinkedList(LinkedList<Action*> *_list) {
            LinkedList<Action*> *newList = new LinkedList<Action*>();
            for (int i = 0; i < _list->size(); i++) {
                Action* action = _list->get(i); 
                newList->add(action);
            }
            return newList;
        }
    public:
        ActionSequence();
        ActionSequence(LinkedList<Action*> *_actionList);
        void add(Action *_action);
        void run();
        void resetActionSequence();
};

#endif