// Header file
#ifndef IRSENSOR_H


#define IRSENSOR_H

class IRSENSOR{
    private:
        bool line;
    public:
        bool getLine();
        bool setLine(bool input);
};

#endif