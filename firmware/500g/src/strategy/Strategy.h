#ifndef STRATEGY_H
#define STRATEGY_H

#include "Node.h"

class Strategy {
    private:
        Node* currNode;
        Node* next(RobotState robotState) {
            return currNode;
        }
    public:
        Strategy() = default;
        void run(Robot* robot) {
            if (currNode == nullptr) currNode = SlammyWammy();
            Vector2<double> output = currNode->strategy(robot->getState());
            robot->getState().currentLeftMotorPow = output.getX();
            robot->getState().currentRightMotorPow = output.getY();
            currNode = this->next(robot->getState());

        }
};

#endif