#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <climits>

using namespace std;
using namespace std::chrono;

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
        swap(array[i], array[rand() % size]);
    }
}

void bubbleSort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);
        }
    }
}

void insertionSort(int array[], int size) {
    int value, index;
    for (int i = 1; i < size; i++) {
        value = array[i];
        index = i;
        while (index > 0 && array[index - 1] > value) {
            array[index] = array[index - 1];
            index--;
        }
        array[index] = value;
    }
}

void selectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++) {
            if (array[minPos] > array[j]) minPos = j;
        }
        swap(array[i], array[minPos]);
    }
}

void gnomeSort(int array[], int size) {
    int ind = 0;
    while (ind < size) {
        if (ind == 0) ind++;
        if (array[ind] >= array[ind - 1]) ind++;
        else {
            swap(array[ind], array[ind - 1]);
            ind--;
        }
    }
}

void heapify(int array[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[largest])
        largest = left;

    if (right < size && array[right] > array[largest])
        largest = right;
    if (largest != i) {
        swap(array[i], array[largest]);
        heapify(array, size, largest);
    }
}

void heapSort(int array[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    for (int i = size - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void shellSort(int array[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];
            array[j] = temp;
        }
    }
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}

void quicksort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void runSortAndMeasure(void (*sortFunc)(int [], int), int array[], int size, string sortName, long long &duration) {
    int *copy = new int[size];
    memcpy(copy, array, size * sizeof(int));
    auto start = high_resolution_clock::now();
    sortFunc(copy, size);
    auto end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " for n=" << size << " took " << duration << " microseconds" << endl;
    delete[] copy;
}

void runSortAndMeasure(void (*sortFunc)(int [], int, int), int array[], int size, string sortName,
                       long long &duration) {
    int *copy = new int[size];
    memcpy(copy, array, size * sizeof(int));
    auto start = high_resolution_clock::now();
    sortFunc(copy, 0, size - 1);
    auto end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " for n=" << size << " took " << duration << " microseconds" << endl;
    delete[] copy;
}

int main() {
    int size10 = 10;
    int size100 = 100;
    int size1000 = 1000;
    srand(time(nullptr));

    int array10[size10], array100[size100], array1000[size1000];
    fillArray(array10, size10);
    fillArray(array100, size100);
    fillArray(array1000, size1000);

    long long durations[8][3] = {{0}};

    cout << "Sorting for n = 10" << endl;
    runSortAndMeasure(bubbleSort, array10, size10, "Bubble Sort", durations[0][0]);
    runSortAndMeasure(insertionSort, array10, size10, "Insertion Sort", durations[1][0]);
    runSortAndMeasure(selectionSort, array10, size10, "Selection Sort", durations[2][0]);
    runSortAndMeasure(gnomeSort, array10, size10, "Gnome Sort", durations[3][0]);
    runSortAndMeasure(heapSort, array10, size10, "Heap Sort", durations[4][0]);
    runSortAndMeasure(shellSort, array10, size10, "Shell Sort", durations[5][0]);
    runSortAndMeasure(quicksort, array10, size10, "Quick Sort", durations[6][0]);
    runSortAndMeasure(mergeSort, array10, size10, "Merge Sort", durations[7][0]);


    cout << "\nSorting for n = 100" << endl;
    runSortAndMeasure(bubbleSort, array100, size100, "Bubble Sort", durations[0][1]);
    runSortAndMeasure(insertionSort, array100, size100, "Insertion Sort", durations[1][1]);
    runSortAndMeasure(selectionSort, array100, size100, "Selection Sort", durations[2][1]);
    runSortAndMeasure(gnomeSort, array100, size100, "Gnome Sort", durations[3][1]);
    runSortAndMeasure(heapSort, array100, size100, "Heap Sort", durations[4][1]);
    runSortAndMeasure(shellSort, array100, size100, "Shell Sort", durations[5][1]);
    runSortAndMeasure(quicksort, array100, size100, "Quick Sort", durations[6][1]);
    runSortAndMeasure(mergeSort, array100, size100, "Merge Sort", durations[7][1]);

    // Sort and measure for n = 1000
    cout << "\nSorting for n = 1000" << endl;
    runSortAndMeasure(bubbleSort, array1000, size1000, "Bubble Sort", durations[0][2]);
    runSortAndMeasure(insertionSort, array1000, size1000, "Insertion Sort", durations[1][2]);
    runSortAndMeasure(selectionSort, array1000, size1000, "Selection Sort", durations[2][2]);
    runSortAndMeasure(gnomeSort, array1000, size1000, "Gnome Sort", durations[3][2]);
    runSortAndMeasure(heapSort, array1000, size1000, "Heap Sort", durations[4][2]);
    runSortAndMeasure(shellSort, array1000, size1000, "Shell Sort", durations[5][2]);
    runSortAndMeasure(quicksort, array1000, size1000, "Quick Sort", durations[6][2]);
    runSortAndMeasure(mergeSort, array1000, size1000, "Merge Sort", durations[7][2]);

    string sortNames[] = {
        "Bubble Sort", "Insertion Sort", "Selection Sort",
        "Gnome Sort", "Heap Sort", "Shell Sort",
        "Quick Sort", "Merge Sort"
    };


    for (int sizeIdx = 0; sizeIdx < 3; ++sizeIdx) {
        long long minDuration = LLONG_MAX;
        long long maxDuration = LLONG_MIN;
        int bestIdx = -1;
        int worstIdx = -1;

        for (int algIdx = 0; algIdx < 8; ++algIdx) {
            if (durations[algIdx][sizeIdx] < minDuration) {
                minDuration = durations[algIdx][sizeIdx];
                bestIdx = algIdx;
            }
            if (durations[algIdx][sizeIdx] > maxDuration) {
                maxDuration = durations[algIdx][sizeIdx];
                worstIdx = algIdx;
            }
        }

        cout << "\nFor n=" << (sizeIdx == 0 ? 10 : sizeIdx == 1 ? 100 : 1000) << ":\n";
        cout << "Best Algorithm: " << sortNames[bestIdx] << " with " << minDuration << " microseconds\n";
        cout << "Worst Algorithm: " << sortNames[worstIdx] << " with " << maxDuration << " microseconds\n";
    }

    return 0;
}
