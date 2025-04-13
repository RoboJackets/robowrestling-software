#include <Arduino.h>

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

class WorldState {
    private:
        IrSensor ir_sensors[9];
        LineSensor line_sensors[4];
    public:
        /*WorldState() : ir_sensors{IrSensor(), IrSensor(), IrSensor(), IrSensor(), IrSensor(), 
                                  IrSensor(), IrSensor(), IrSensor(), IrSensor()}, 
                       line_sensors{LineSensor(), LineSensor(), LineSensor(), LineSensor()} {
            // Constructor body (if needed)
        }*/
       /*dictionary mapping between line sensors enumerations and enemy positions, return left if enemy at left, right if enemy at right, etc., mappings atnd constructors*/
        int getEnemyPos();
        bool getAtBoundary();
};

#endif