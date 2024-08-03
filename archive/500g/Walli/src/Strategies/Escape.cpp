#include <Robot/Walli.h>

/*This is what is run whenever we hit an edge.
* we move in the opposite direction of the line and swerve out
*/
class Escape {
    private:
        Walli* walli;
    public:
        Escape(Walli* w) {
            walli = w;
        }

        void run() {
            //we escape for a certain amount of time
            int start = millis();
            //if we're on the front line
            if (walli->onFrontLine()) {
                //swerve backwards and to the left
                walli->reverse();
                walli->turnLeft();
            } else if (walli->onBackLine()){
                //swerve forwards and to the right if we're on the front line
                walli->forward();
                walli->turnRight();
            }
            //if we ran out of time, switch to attack
            if (start - millis() < 0 ) {
                return;
            }
        }
};