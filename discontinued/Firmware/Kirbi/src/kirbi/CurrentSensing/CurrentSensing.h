#include "math.h"

double voltage_to_current;
double tw; //thermal time constant
double precalc; //nominal_current*(sqrt(r1/(r1+r2)))

void getCurrentFromVoltage();
void getTimeFromCurrent();