template <typename T>
class CircularArray {
    T array[];
    int index = 0;
    public:
        CircularArray(int inital_capacity){
            array = new T[inital_capacity];
        }

        void add(T[] arr) {
            array[index] = arr;
            index = (index + 1) % array.length;
        }

        T[] get(int i) {
            return array[i];
        }

        T[] getFront(){
            return array[index];
        }
};