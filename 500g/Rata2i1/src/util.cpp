//class with helper methods for other classes
#include "util.h"

int util::average(int values[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += values[i];
    }
    return sum / size;
}