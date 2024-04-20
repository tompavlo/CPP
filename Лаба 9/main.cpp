#include <iostream>
using namespace std;
bool isCompleteGraph(int graph[4][4], int size) {

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(i!=j && graph[i][j]==0) return false;
        }
    }

    return true;
}

int main() {
    int graph[4][4] = {
        {0, 0, 4, 0},
        {0, 0, 6, 3},
        {4, 6, 0, 7},
        {0, 3, 7, 0}
    };
    cout <<"Чи граф повний?\n"<<boolalpha<< isCompleteGraph(graph,4);
}
