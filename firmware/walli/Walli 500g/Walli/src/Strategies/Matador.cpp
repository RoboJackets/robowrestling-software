#include<Robot/Walli.h>

class Matador {
    private:
        Walli walli;
    public:
        Matador(Walli w) {
            walli = w;
        }

        void run() {
            if(walli.onFrontLine() || walli.onBackLine()) {
                return;
            }
            int start1 = millis();
            if (millis() - start1 < 500) {
                walli.turnRight();
            }
            if (!walli.onFrontLine()) {
                walli.forward();
            }
            int start2 = millis();
            if (millis() - start2 < 500) {
                walli.turnLeft();
            }
            if (!walli.onFrontLine()) {
                walli.forward();
            }
            int start3 = millis();
            if (millis() - start3 < 500) {
                walli.turnLeft();
            }
            if (!walli.onFrontLine()) {
                walli.forward();
            }
        }
};