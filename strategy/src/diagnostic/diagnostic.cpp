#include <strategy/diagnostic/diagnostic.h>

void check_motor() {
    drive(127,255);
    delay(1000);
    drive(0,0);
    drive(63,191);
    delay(1000);
    drive(0,0);
}

void check_line_sensor() {
	get_line_flag();
}