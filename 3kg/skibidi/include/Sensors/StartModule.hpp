#ifndef STARTMODULE_HPP_
#define STARTMODULE_HPP_

#include <Arduino.h>

class StartModule {
    private:
        int pin_number;
    public:
        StartModule(int pin_number);
        bool is_started();
};

#endif // STARTMODULE_HPP_
