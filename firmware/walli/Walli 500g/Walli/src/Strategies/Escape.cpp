#include <Robot/Walli.h>

class Escape {
    private:
        Walli* walli;
    public:
        Escape(Walli* w) {
            walli = w;
        }

        void run() {
            if (walli->onFrontLine()) {
                walli->reverse();
            } else if (walli->onBackLine()){
                walli->forward();
            } else {
                return;
            }
        }
};