#include <Robot/Walli.h>

/* This is the "SlammyWhammy" attack.
* Walli will spin until the opponent is detected
* directly in front of him.
* Then, he goes forward until he hits a line.
* the method returns when we hit a line and should transition
* to escape.
*/
class SlamAttack {
    //private stuff cause encapsulation
    private:
        //this stores a reference to the main Walli object
        Walli* walli;
    public:
        //constructor
        SlamAttack(Walli* w) {
            walli = w;
        }

        //the actual strategy
        void run() {
            //once we hit a line, stop the strategy immedietly
            if (walli->onFrontLine() || walli->onBackLine()) {
                return;
            } else if (walli->centerDetected()) {
                //we found the opponent, full speed ahead
                walli->forward();
            } else if (!walli->leftDetected()) {
                //the bot isn't on our left, so it must be on our right
                //so we move to the right
                walli->turnRight(); 
            } else if (!walli->rightDetected()){
                //the bot isn't on our right, so it must be on our left
                //so we move to the left
                walli->turnLeft();
            }
        }
};