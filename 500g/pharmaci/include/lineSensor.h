#ifndef LINESENSOR_H
#define LINESENSOR_H
class lineSensor {
    private: 
        bool lineDetected;
    public: 
        lineSensor();
        bool getLineSensor();
        void setLineSensor(bool value);
};
#endif
