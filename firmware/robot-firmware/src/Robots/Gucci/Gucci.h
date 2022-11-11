#ifndef GUCCI_H
#define GUCCI_H

#include "Robots/Robot.h"
#include "Sensors/TFMini/TFMini.h"

class Gucci : public Robot {
private: 
    TFMini *frontOne; 
public: 
    Gucci() {
        //TODO: replace these with the actual pin values
        frontOne = new TFMini(0,1); 
        _sensors[0] = frontOne;  
    }

    void UpdateState() override {
        _state.lidars[0] = frontOne -> GetDistance(); 
    } 


}; 

#endif 