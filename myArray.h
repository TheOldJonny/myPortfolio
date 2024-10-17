class Array
{
    public:
        Array(int length, int size,  bool autoInitialize = false);
        Array(int *A, int length, int size);
        Array(Array &sourceArray);
        ~Array();
        void display();
        void append(int value);
        void insert(int index, int x);
        void remove(int index);
        int linearSearch(int value, int startingIndex = 0);
        int min();
        int max();
        void sort();
        int binarySearch(int value); // to be used only if the array is sorted
        int get(int index);

        
        void set(int index, int value);
        int sum();
        int average();
        void reverse();
        void reverse_v2();
        void leftShift();
        void leftRotation();
        void rightShift();
        void rightRotation();

        bool isSorted();
        void insertInSortedArray(int value);
        Array merge(Array *secondArray);
        void mergeInPlace(Array *secondArray);
        void deleteAllOccurrencies(int value);
        void deleteReplicates(int value);


        bool compare(Array *secondArray);
        void unique();

        int countOccurrences(int value);
        void setIntersection(Array *secondArray);
        void setUnion(Array *secondArray);
        void setDifference(Array *secondArray);



    private:
        int *A;
        int size;
        int length;

};