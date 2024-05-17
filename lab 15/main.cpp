#include <iostream>

using namespace std;

void fillArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 501 - 100;
    }
}

void print(int array[], int size) {
    for (int i = 0; i < size; i++)
        cout << array[i] << ' ';
    cout << endl;
}

void shuffle(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = array[rand() % size];
    }
}

void bubbleSort(int array[], int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(array[j]>array[j+1]) swap(array[j], array[j+1]);
        }
    }
}

void insertionSort(int array[], int size) {
    
}

int main() {
    int size10 = 10;
    int size100 = 100;
    int size1000 = 1000;
    srand(time(nullptr));
    int array10[size10];
    int array100[size100];
    int array1000[size1000];
    fillArray(array10, size10);
    fillArray(array100, size100);
    fillArray(array1000, size1000);
    bubbleSort(array10, size10);
    print(array10, size10);
    return 0;
}
