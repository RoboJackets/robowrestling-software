#ifndef RobotActions_hpp

#define RobotActions_hpp

class RobotActions {
    private:
        int *driver[2];
    
    public:
        RobotActions(int *left, int *right);
        int getLeft();
        int getRight();
        void setLeft(int spd);
        void setRight(int spd);
        void forward(int spd);
        void backward(int spd);
        void turnLeft(int spd);
        void turnRight(int spd);
};

#endif