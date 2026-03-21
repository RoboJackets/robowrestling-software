#ifndef RobotActions_hpp

#define RobotActions_hpp

class RobotActions {
    private:
        int *driver[2];
        unsigned long endTime;
        int priority;
    
    public:
        RobotActions(int *left, int *right);
        int getLeft();
        int getRight();
        void setLeft(int spd, int time = 0, int priority = 0);
        void setRight(int spd, int time = 0, int priority = 0);
        void forward(int spd, int time = 0, int priority = 0);
        void backward(int spd, int time = 0, int priority = 0);
        void turnLeft(int spd, int time = 0, int priority = 0);
        void turnRight(int spd, int time = 0, int priority = 0);
        bool actionOver();
};

#endif