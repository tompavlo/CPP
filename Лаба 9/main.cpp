#include <iostream>


using namespace std;
int graph[4][4] = {
    {0, 0, 4, 0},
    {0, 0, 6, 3},
    {4, 6, 0, 7},
    {0, 3, 7, 0}
};

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
    bool isIzolated = false;
    int closest;
    int counter = 0;
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
        if (isIzolated) cout << "Node " << i + 1 << " is izolated, distance to closest object - " << closest << endl;
    }
    cout << "Total izolated: " << counter << endl;
}

int findMaxPath(int from, int ex = -1) {
    int max = 0;
    int id = -1;
    for (int i = 0; i < 4; i++) {
        if (i != from && i != ex && graph[from][i] > max) {
            max = graph[from][id];
            id = i;
        }
    }
    return id;
}

bool isInArr(int *arr, int n, int v) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == v) return true;
    }
    return false;
}

bool findCompletePath(int path[], int id, int n, int prev = 0) {
    bool stop;
    for (int i = 0; i < n; i++) {
        if (id == 0) {
            path[id] = i;
            stop = findCompletePath(path, id + 1, n, i);
        } else if (graph[prev][i] != 0 && !isInArr(path, n, i)) {
            path[id] = i;
            if (id == n - 1) return true;
            stop = findCompletePath(path, id + 1, n, i);
        } else {
            path[id] = -1;
        }

        if (stop) return stop;
        if (id == 0 && i == n - 1) return false;
    }
    return stop;
}

int main() {
    int size = 4;
    cout << "Чи граф повний?\n" << boolalpha << isCompleteGraph(graph, 4) << endl;
    printAdjacencylist(graph, 4);
    cout << "Average lenght: " << avgLength(graph, 4) << endl << endl;
    cout << "Izolated:\n";
    printIzolated(graph, 4);
    cout << "\n\nНайдовший шлях: ";
    struct path {
        int p1, p2, p3, r1, r2;
    } max, cur;
    max.p1 = -1;
    for (int i = 0; i < size; i++) {
        cur.p1 = i;
        cur.p2 = findMaxPath(cur.p1);
        cur.r1 = graph[cur.p1][cur.p2];
        cur.p3 = findMaxPath(cur.p2, cur.p1);
        cur.r2 = graph[cur.p2][cur.p3];

        if (max.p1 == -1 || (cur.r1 + cur.r2 > max.r1 + max.r2 && cur.r1 != 0 && cur.r2 != 0)) {
            max.p1 = cur.p1;
            max.p2 = cur.p2;
            max.p3 = cur.p3;
            max.r1 = cur.r1;
            max.r2 = cur.r2;
        }
    }
    cout << "(" << max.p1 + 1 << ") --- " << max.r1 << " --- (" << max.p2 + 1 << ") --- " << max.r2 << " --- (" << max.
            p3 + 1 << ")\n";

    int path[6];
    bool canPath = findCompletePath(path, 0, size);
    if (canPath) {
        cout << "Можливо об'їхати всі пункти, заїжджаючи тільки один раз\n";
        cout << "Можливий шлях: ";
        for (int i = 0; i < size; i++) {
            cout << path[i] + 1 << " ";
        }
    } else {
        cout << "Не можливо об'їхати всі пункти, заїжджаючи тільки один раз\n";
    }
}
