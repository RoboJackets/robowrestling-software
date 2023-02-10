#ifndef TURN_H
#define TURN_H
#include "Behaviors/Nodes/SequenceNode.h"

namespace BT {
    class Turn : public BT::Node<T> {    
        public:
            Turn (int turnSpeed, double turnAngle) {
                this -> turnSpeed = turnSpeed;
                this -> turnAngle = turnAngle;
                this -> lidarDist = lidarDist;
            }

            Turn () {
                this -> turnSpeed = 0;
                this -> turnAngle = 0.0;
            }

            U Run(T input) override {
                
            }

            int getTurnSpeed() {
                return this -> turnSpeed;
            }

            int getTurnAngle() {
                return this -> turnAngle;
            }

        private:
            int turnSpeed;
            double turnAngle;
            int lidarDist;
    }
}