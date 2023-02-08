#include "TimeVoltage.h"


// double r1 - Thermal resistance winding - housing
// double r2 - Thermal resistance housing - ambient
// double nominal_current - Explanatory
// double tw - thermal time constant
void setValues(double r1, double r2, double nominal_current, double tw_in, double v_to_c) {
    precalc = 1 / nominal_current * sqrt(r1 / (r1 + r2));
    voltage_to_current = v_to_c;
    tw = tw_in;
}

double getCurrent(double voltage) {
    return voltage * voltage_to_current;
}

double getTimeFromCurrent(double current) {
    double K = current * precalc;
    double t_on = tw * log(pow(K,2)/(pow(K,2) + 1));
    return t_on;
}
