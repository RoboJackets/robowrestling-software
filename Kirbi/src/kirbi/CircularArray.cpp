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
            index = (index + 1) % array.length;
        }

        T get(int i) {
            return array[i];
        }

        T getFront(){
            return array[index];
        }
}