#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

class line_sensor {
    private:
        int value;

    public:
        line_sensor();
        line_sensor(int value);
        void set_value(int new_value);
        int get_value();
};


#endif