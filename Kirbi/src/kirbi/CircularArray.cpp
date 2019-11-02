template <typename T>
class CircularArray {
    T array[];
    int index;
    public:
        CircularArray(int inital_capacity){
            array = new T[inital_capacity];
            index = 0;
        }

        void add(T data) {
            array[index] = data;
            index++;
            if (index == array.length) {
                index = 0;
            }
        }

        T get(int i) {
            return array[i];
        }

        T getFront(){
            if (index != 0) {
                return array[index-1];
            }
            return array[array.length-1];
        }
};