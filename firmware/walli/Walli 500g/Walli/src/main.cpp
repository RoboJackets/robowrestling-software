#include <Robot/Walli.h>
#include <Strategies/Escape.cpp>
#include <Strategies/Matador.cpp>
#include <Strategies/SlamAttack.cpp>
#include <State Machine/StateController.cpp>
#include <State Machine/StateS.cpp>

Walli walli;
StateS start;
StateS attack;
StateS escape;
StateS off;
StateController sc;
Matador m;
SlamAttack slam;
Escape e;
void setup() {
    walli = *new Walli(A4, A5, A6, A9, A10, A11, A12, A0, A1, A2, A3);
    sc = *new StateController();
    off = sc.getCurrent();
    start = *new StateS(State::START);
    attack = *new StateS(State::ATTACK);
    escape = *new StateS(State::ESCAPE);
    start.setNext(&attack);
    attack.setNext(&escape);
    escape.setNext(&attack);
    m = *new Matador(walli);
    slam = *new SlamAttack(walli);
    e = *new Escape(walli);

}

void loop() {
    if (sc.getCurrent() == off.getState()) {
        sc.transition();
    }
    switch(sc.getCurrent()) {
        case START:
            m.run();
            start.setCondition(true);
            break;
        case ATTACK:
            slam.run();
            attack.setCondition(true);
            break;
        case ESCAPE:
            e.run();
            escape.setCondition(true);
            break;
    }
}