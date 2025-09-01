#ifndef RobotActions_hpp

#define RobotActions_hpp

class RobotActions {
    private:
        int driver[2];
    
    public:
        RobotActions(int left, int right);
        int getLeft();
        int getRight();
        
        void Forward(int left, int right);
};

#endif