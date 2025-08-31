# ifndef IRSensor_HPP

# define IRSensor_HPP

class IRSensor {
    private:
        int val;

    public:
        IRSensor();
        int getVal();
        void setVal(int newVal);
};

# endif