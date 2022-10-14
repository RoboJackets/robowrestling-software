/*
    0V (full BAK) - 5V (full FWD), 2.5V no motion

    DIP switch 4 controls analog mode
    Switch up = Mixed (differential drive)
        - S1 controls FWD/BAK, S2 controls turning
        - ** ASSUMED AS DEFAULT IN CODE **
    Switch down = Independant
        - S1 controls motor 1, S2 control motor 2
*/
#define PIN_S1 0
#define PIN_S2 1

/*
    Movement functions
*/
void move(double voltage, bool individual = false);
void turn(double voltage, bool individual = false);

void stop();
