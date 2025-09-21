#include "sensor.hpp"


sensor::sensor(int sensorValue){

    value = sensorValue;

}
int sensor::getValue(){
    return value;
}
void sensor::setValue(int t){

   if(t ==1){
    if(concurrency >=10){
        value = 1;
        }
    else{
        
        concurrency++;
    }

   }
   else{
    value = 0;
    concurrency=0;
   }
   
   
}