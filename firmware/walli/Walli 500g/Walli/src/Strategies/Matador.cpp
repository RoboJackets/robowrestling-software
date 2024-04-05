#include<Robot/Walli.h>

/*This is the opening strategy we saw in the recruitment video
* Moves in a right triangle-ish formation to get behind the opponenent immedietly
* hopefully would push the bot off?
* Note that is experimental and we might have to scrap
*/

class Matador {
    private:
        //stores the walli reference
        Walli* walli;
    public:
        //constructor
        Matador(Walli* w) {
            walli = w;
        }

        //I actually don't think that this will work
        //but we can try!
        void run() {
            //if we're starting on a line, immedietly stop
            if(walli->onFrontLine() || walli->onBackLine()) {
                return;
            }
            //while we haven't run out of some arbitary time (fix)
            int start1 = millis();
            if (millis() - start1 < 500) {
                //turn to the right
                walli->turnRight();
            }
            //while we're not on the line, move forward
            //can fix to use time as well
            if (!walli->onFrontLine()) {
                walli->forward();
            }
            //while we haven't run out of some arbitrary time (fix)
            int start2 = millis();
            if (millis() - start2 < 500) {
                //turn left
                walli->turnLeft();
            }
            //while we're not on the line, move forward
            //can fix to use time as well
            if (!walli->onFrontLine()) {
                walli->forward();
            }
            //while we haven't run out of some arbitrary time (fix)
            int start3 = millis();
            if (millis() - start3 < 500) {
                //turn left
                walli->turnLeft();
            }
            //here, we should be just behind the robot
            //switch to attack
            if (!walli->onFrontLine()) {
                return;
            }
        }
};