/*

 * Ahmad Nour Haidar

 */
#include <bits/stdc++.h>

using namespace std;

#define type int

/// Note: indices start from 0.

class MaxHeap {
private:
    type *array;  /// pointer to array
    int maxSize;
    int currentSize;

    static int _parent(int i) {
        return ((i - 1) / 2);
    }

    static bool _hasParent(int i) {
        return (_parent(i) >= 0);
    }

    static int _leftChild(int i) {
        return (2 * i + 1);
    }

    static int _rightChild(int i) {
        return (2 * i + 2);
    }

    static void _swap(type &first, type &second) {
        type temp = first;
        first = second;
        second = temp;
    }

/****************************************************************************************************************/

    //// heapify
    /// Time Complexity: O(log n) for each element.
    void _maxHeapifyBottomUp(int i) {
        int parent = _parent(i);
        if (array[i] > array[parent]) {
            _swap(array[i], array[parent]);
            _maxHeapifyBottomUp(parent);
        }
    }

    /// Time Complexity: O(log n) for each element.
    void _maxHeapifyTopDown(int i) {
        int largest = i;
        int left = _leftChild(i);
        int right = _rightChild(i);
        if (left < currentSize and array[left] > array[largest]) {
            largest = left;
        }
        if (right < currentSize and array[right] > array[largest]) {
            largest = right;
        }
        if (largest not_eq i) {
            _swap(array[largest], array[i]);
            _maxHeapifyTopDown(largest);
        }
    }

    //// insert
    /// Time Complexity: O(log n) for each element.
    void _insert(const type &newElement) {
        array[currentSize] = newElement;
        _maxHeapifyBottomUp(currentSize);
        currentSize++;
    }

    //// delete
    /// Time Complexity: O(log n) for each element.
    void _deleteRoot() {
        type lastElement = array[currentSize - 1];
        array[0] = lastElement;
        currentSize--;
        _maxHeapifyTopDown(0);
    }

    /// Time Complexity: O(log n) for each element.
    void _deleteAtIndex(const int &index) {
        array[index] = array[currentSize - 1];
        int parent = _parent(index);
        currentSize--;
        if (array[index] > array[parent]) {
            _maxHeapifyBottomUp(index);
        } else {
            _maxHeapifyTopDown(index);
        }
    }

    /// Time Complexity: O(1) for each element.
    void _deleteAtEnd() {
        currentSize--;
    }

    /****************************************************************************************************************/

    //// print
    static const int SPACE = 3;

    /// Time Complexity: O(log n)
    /// Auxiliary Space: O(1)
    static int _power(int x, unsigned n) {
        int result = 1;
        while (n) {
            if (n & 1) {
                result = result * x;
            }
            x = x * x;
            n >>= 1;
        }
        return result;
    }

    static void _print_space(int &n) {
        for (int i = 0; i < n; ++i) {
            cout << ' ';
        }
    }

    static void _print_line() {
        for (int i = 0; i < 100; ++i) {
            cout << '=';
        }
        cout << endl;
    }

    /// Time Complexity: O(log n)
    /// Auxiliary Space: O(1)
    static int _log(int x) {
        int c = 0;
        while (x) {
            c++;
            x /= 2;
        }
        return c;
    }

    int _count_levels() const {
        int l = _log(currentSize);
        int nodes = _power(2, l);
        if (currentSize > nodes)l++;
        return l;
    }

    void _print_hierarchically() {
        int w = 3;
        int count_level = _count_levels();
        int c = 0;
        for (int i = 0; i < count_level; ++i) {
            int len = _power(2, i);
            int first = _power(2, count_level - i - 1) - 1;
            first *= SPACE;
            _print_space(first);
            int between = _power(2, count_level - i);
            between *= SPACE;
            between -= w;
            for (int j = 0; j < len and c < currentSize; ++j) {
                cout << setw(w) << array[c];
                /// don't print after last value in the level
                if (j < len - 1 and j < c) {
                    _print_space(between);
                }
                c++;
            }
            cout << endl;
        }
    }

    void _print() {
        for (int i = 0; i < currentSize; ++i) {
            cout << array[i] << ' ';
        }
        cout << '\n';
    }

public:

    /// constructor
    MaxHeap(int maxSize) {
        this->maxSize = maxSize;
        array = new type[maxSize];
        currentSize = 0;
    }

    /// Time Complexity: O(1) for each element.
    bool isFull() {
        return currentSize == maxSize;
    }

    /// Time Complexity: O(1) for each element.
    bool isEmpty() {
        return currentSize == 0;
    }

    /// Time Complexity: O(log n) for each element.
    void insert(const type &newElement) {
        if (isFull()) {
            cout << "Sorry, your heap is full.\n";
            return;
        }
        _insert(newElement);
    }

    /// Time Complexity: O(log n) for each element.
    void deleteRoot() {
        if (isEmpty()) {
            cout << "Sorry, your heap is empty.\n";
            return;
        }
        _deleteRoot();
    }

    /// Time Complexity: O(1) for each element.
    void deleteAtEnd() {
        if (isEmpty()) {
            cout << "Sorry, your heap is empty.\n";
            return;
        }
        _deleteAtEnd();
    }

    /// Time Complexity: O(log n) for each element.
    void deleteAtIndex(const int &index) {
        if (index < 0 or index >= currentSize) {
            cout << "Sorry, out of bound.\n";
            return;
        }
        _deleteAtIndex(index);
    }

    void print() {
        if (isEmpty()) {
            cout << "Sorry, your heap is empty.\n";
            return;
        }
        _print();
    }

    void print_hierarchically() {
        if (isEmpty()) {
            cout << "Sorry, your heap is empty.\n";
            return;
        }
        _print_hierarchically();
        _print_line();
    }
    //// end class MaxHeap
};

int main() {

    MaxHeap maxHeap(20);

    maxHeap.insert(2);
    maxHeap.print();
    maxHeap.insert(5);
    maxHeap.print();
    maxHeap.insert(4);
    maxHeap.print();
    maxHeap.insert(5);
    maxHeap.print();
    maxHeap.insert(48);
    maxHeap.print();
    maxHeap.insert(44);
    maxHeap.print();
    maxHeap.insert(0);
    maxHeap.print();
    maxHeap.insert(2);
    maxHeap.print();
    maxHeap.insert(47);
    maxHeap.print();
    maxHeap.insert(65);
    maxHeap.print();
    maxHeap.insert(89);
    maxHeap.print();
    maxHeap.insert(88);
    maxHeap.print();
    maxHeap.insert(100);
    maxHeap.print();
    maxHeap.insert(123);
    maxHeap.print();
    maxHeap.insert(-9);
    maxHeap.print();
    maxHeap.insert(5);
    maxHeap.print();
    maxHeap.insert(33);
    maxHeap.print();
    maxHeap.insert(1);
    maxHeap.print();
    maxHeap.insert(3);
    maxHeap.print();
    maxHeap.insert(0);
    maxHeap.print();
    maxHeap.deleteAtIndex(1);
    maxHeap.print();
    maxHeap.deleteAtEnd();
    maxHeap.print();
    maxHeap.deleteRoot();
    maxHeap.print();
    maxHeap.print_hierarchically();
    maxHeap.deleteAtIndex(2);
    maxHeap.print_hierarchically();

    return 0;
}