#include <Robot/Walli.h>

class SlamAttack {
    private:
        Walli walli;
    public:
        SlamAttack(Walli w) {
            walli = w;
        }
        void run() {
            if (walli.onFrontLine() || walli.onBackLine()) {
                return;
            } else if (walli.centerDetected()) {
                walli.forward();
            } else if (!walli.leftDetected()) {
                walli.turnRight();
            } else {
                walli.turnLeft();
            }
        }
};