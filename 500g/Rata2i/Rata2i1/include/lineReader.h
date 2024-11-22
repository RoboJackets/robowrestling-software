#ifndef LINE_READER_H
#define LINE_READER_H
class lineReader{
    private:
        int value;
        int readings[10];
        int threshold;
        int counter;
    public:
        lineReader();
        lineReader(int value);
        int getValue();
        void setValue(int value);
        int getThreshold();
        void setThreshold(int threshold);
};
#endif