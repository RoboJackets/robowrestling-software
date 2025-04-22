#ifndef LINE_READER_H
#define LINE_READER_H
class lineReader{
    private:
        int value;
        double average;
        int readings[10];
        int threshold;
        int counter;
    public:
        lineReader();
        lineReader(int value);
        lineReader(int value, int threshold);
        int getValue();
        double getAverage();
        void setValue(int value);
        int getThreshold();
        void setThreshold(int threshold);
};
#endif