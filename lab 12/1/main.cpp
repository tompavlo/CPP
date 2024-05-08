#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> vector) {
    for(int i : vector) {
        cout<<i<<' ';
    }
}
int main() {
    vector<int> vector;
    int numb;
    for(int i=0; i<10; i++) {
        cout<<"Input number: ";
        cin>>numb;
        vector.push_back(numb);
    }
    printVector(vector);
    cout<<endl;
    vector[1]=10;
    printVector(vector);
    cout<<endl;
    vector.pop_back();
    printVector(vector);
    vector.front()=25;
    cout<<endl;
    printVector(vector);

    return 0;
}
