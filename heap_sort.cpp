

///  Ahmad Nour Haidar

#include <iostream>

#define endl '\n'
#define type int

using namespace std;

/// Heap Sort: Time Complexity = (n * log(n))
template<class T>
class HeapSort {
    /* This class only for sorting array
     * Note: values store in array from index 0 so:
     * left child  = 2*i+1
     * right child = 2*i+2
     * */
private:

    void build_max_heap(T *array, int length) {
        for (int i = length / 2 - 1; i >= 0; --i) {
            _max_heapify(array, length, i);
        }
    }

    void _max_heapify(T *array, int length, int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if (left < length and array[left] > array[largest]) {
            largest = left;
        }
        if (right < length and array[right] > array[largest]) {
            largest = right;
        }
        if (largest not_eq index) {
            _swap(array[index], array[largest]);
            _max_heapify(array, length, largest);
        }
    }

    void build_min_heap(T *array, int length) {
        for (int i = length / 2 - 1; i >= 0; --i) {
            _min_heapify(array, length, i);
        }
    }

    void _min_heapify(T *array, int length, int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if (left < length and array[left] < array[largest]) {
            largest = left;
        }
        if (right < length and array[right] < array[largest]) {
            largest = right;
        }
        if (largest not_eq index) {
            _swap(array[index], array[largest]);
            _min_heapify(array, length, largest);
        }
    }

    void _swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    void descending_heap_sort(T *array, int length) { // height to min
        build_min_heap(array, length);
        for (int i = length - 1; i >= 0; --i) {
            _swap(array[0], array[i]);
            _min_heapify(array, i, 0);
        }
    }

    void ascending_heap_sort(T *array, int length) { // min to height
        build_max_heap(array, length);
        for (int i = length - 1; i > 0; --i) {
            _swap(array[0], array[i]);
            _max_heapify(array, i, 0);
        }
    }

    void print(T *array, int length) {
        for (int i = 0; i < length; ++i) {
            cout << array[i] << ' ';
        }
        cout << endl;
    }
};


int main() {

    HeapSort<int> h;
    int a[] = {57, 986, 32, 0, 14, -9, 6, 5, 4, 7,
               32, 14, 52, 698, 47, -96, -85, -9,
               -21, 14, 21, 14, 21, -9, -88, 1, 5, 48};

    int len = sizeof(a) / sizeof(a[0]);

    h.print(a, len);

    h.ascending_heap_sort(a, len);
    h.print(a, len);

    h.descending_heap_sort(a, len);
    h.print(a, len);

    return 0;
}