#include <iostream>

#include "../../../../../../../cygwin64/usr/include/limits.h"
using namespace std;

bool isCompleteGraph(int graph[4][4], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j && graph[i][j] == 0) return false;
        }
    }

    return true;
}

void printAdjacencylist(int graph[4][4], int size) {
    cout << "Adjacency list:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ": ";
        for (int j = 0; j < size; j++) {
            if (graph[i][j] != 0) cout << j + 1 << ' ';
        }
        cout << endl;
    }
}

double avgLength(int graph[4][4], int size) {
    double result = 0;
    int counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (graph[i][j] != 0) {
                result += graph[i][j];
                counter++;
            }
        }
    }
    return result / counter;
}

void printIzolated(int graph[4][4], int size) {
    bool isIzolated=false;
    int closest;
    int counter=0;
    for (int i = 0; i < size; i++) {
        isIzolated = false;
        for (int j = 0; j < size; j++) {
            if (graph[i][j] != 0) {
                if (isIzolated) {
                    isIzolated = false;
                    counter--;
                    break;
                }
                isIzolated = true;
                counter++;
                closest = graph[i][j];
            }
        }
        if (isIzolated) cout<<"Node " << i + 1 << " is izolated, distance to closest object " << closest;
    }
}

int main() {
    int graph[4][4] = {
        {0, 0, 4, 0},
        {0, 0, 6, 3},
        {4, 6, 0, 7},
        {0, 3, 7, 0}
    };
    cout << "Чи граф повний?\n" << boolalpha << isCompleteGraph(graph, 4) << endl;
    printAdjacencylist(graph, 4);
    cout << "Average lenght: " << avgLength(graph, 4) << endl << endl;
    cout<<"Izolated:\n";
    printIzolated(graph, 4);
}
