#include <iostream>

using namespace std;

void bubbleSort(int* array, int size) {
    for (int i=0; i<size; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(array[j]>array[j+1]) swap(array[j], array[j+1]);
        }
    }
}

void insertionSort(int* array, int size) {
    for(int i=1; i<size; i++) {
        int key=array[i];
        int j=i-1;
        while(j>=0 && array[j]>key) {
            array[j+1]=array[j];
            j--;
        }
        array[j+1]=key;
    }

}

void gnomeSort(int* array, int size) {
    int i=1;
    while (i<size) {
        if (array[i-1]<=array[i]) i++;
        else {
            swap(array[i-1], array[i]);
            i--;
            if(i==0) i++;
        }
    }
}

void selectionSort(int* array, int size) {
    for(int i=0; i<size-1; i++) {
        int minInd=i;
        for(int j=i; j<size; j++) {
            if(array[minInd]>array[j]) minInd=j;
        }
        swap(array[minInd], array[i]);
    }

}

void shuffle(int* array, int size) {
    for(int i=0; i<size; i++) {
        swap(array[i], array[rand()%size]);
    }
}

void fillArray(int* array, int size) {
    for(int i=0; i<size; i++) {
        array[i]=rand()%50-20;
    }
}

void printArray(int* array, int size) {
    for(int i=0; i<size; i++) {
        cout<<array[i]<<' ';
    }
    cout<<endl;
}

int binarySearch(int* array, int size, int x,int high, int low=0) {
    while(low<=high) {
        int mid=low+(high-low)/2;
        if(array[mid]==x) return mid;
        if(array[mid]<x) low=mid+1;
        else high=mid-1;
    }
    return -1;
}
int main() {
    srand(time(nullptr));
    int array[100];
    int size=100;
    fillArray(array,size);
    bubbleSort(array, size);
    printArray(array, size);
    shuffle(array, size);
    selectionSort(array, size);
    printArray(array, size);
    shuffle(array, size);
    insertionSort(array, size);
    printArray(array, size);
    shuffle(array, size);
    gnomeSort(array, size);
    printArray(array, size);
    cout<<binarySearch(array, size, 29, size-1);
    return 0;
}
