#ifndef IR_SENSOR_H
#define IR_SENSOR_H

class ir_sensor {
    private:
        bool ir_sense;

    public:
        ir_sensor();
        ir_sensor(bool ir_sense);
        void set_ir_sensor(bool new_ir_sense);
        bool get_ir_sensor();
};


#endif