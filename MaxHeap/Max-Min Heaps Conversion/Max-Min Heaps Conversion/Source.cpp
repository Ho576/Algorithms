#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Heap {
private:
    vector<int> heap;

    void maxHeap(int index) {
        while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void minHeap(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            minHeap(smallest);
        }
    }


    void convertToMinHeap() {
        int calculationOfIndex = heap.size() / 2 - 1;
        for (int i = calculationOfIndex; i >= 0; --i) {
            minHeap(i);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        maxHeap(heap.size() - 1);
    }

    void printHeap() {
        int size = heap.size();
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    void convertToMinHeapAndPrint() {
        convertToMinHeap();
        cout << "Min-Heap:" << endl;
        printHeap();
    }
};

int main() {
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    Heap heap;

    int value;
    while (inputFile >> value) {
        heap.insert(value);
    }

    cout << "Max-Heap:" << endl;
    heap.printHeap();
    heap.convertToMinHeapAndPrint();
    inputFile.close();


}