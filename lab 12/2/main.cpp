#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<int> > matrix(5, vector<int>(5));
    srand(time(nullptr));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = rand() % 9 + 1;
        }
    }
    cout << "Matrix";
    for (int i = 0; i < 5; i++) {
        cout << endl;
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << ' ';
        }
    }
    cout << endl;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        cout << "Sum for row " << i + 1 << " :";
        for (int j = 0; j < 5; j++) {
            sum += matrix[i][j];
        }
        cout << sum << endl;
        sum = 0;
    }
    for (int i = 0; i < 5; i++) {
        cout << "Sum for column " << i + 1 << " :";
        for (int j = 0; j < 5; j++) {
            sum += matrix[j][i];
        }
        cout << sum << endl;
        sum = 0;
    }
}
