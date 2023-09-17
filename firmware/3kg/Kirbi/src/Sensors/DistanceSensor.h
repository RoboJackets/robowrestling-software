#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

template<typename T>
class DistanceSensor {
public:

   virtual T GetDistance() = 0;
   DistanceSensor() {}
   ~DistanceSensor() {}

protected: 
    T _distance; 

 

}; 

#endif 