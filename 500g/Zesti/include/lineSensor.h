#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
    private: 
        bool lineDetected;
    public: 
        LineSensor();
        bool getLineSensor();
        void setLineSensor(bool value);
};

#endif
