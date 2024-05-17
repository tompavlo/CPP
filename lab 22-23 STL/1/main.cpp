#include <iostream>
#include <list>

using namespace std;

int totalUnique(list<int> userList) {
    userList.unique();
    return userList.size();
}
int main() {
    list<int> userList;
    for (int i = 0; i < 10; i++) {
        cout << "Input number: ";
        int data;
        cin >> data;
        userList.push_back(data);
    }
    cout << "List: ";
    for (int i: userList) {
        cout << i << ' ';
    }
    cout<<endl;
    userList.sort();
    list<int> randomList;
    srand(time(nullptr));
    for (int i = 0; i < 10; i++) {
        randomList.push_back(rand() % 50 + 1);
    }
    randomList.sort();
    cout << "Random list: ";
    for (int i: randomList) {
        cout << i << ' ';
    }
    cout<<endl;
    cout<<"Merged list: ";
    randomList.merge(userList);
    for (int i: randomList) {
        cout << i << ' ';
    }
    cout<<"\nTotal unique numbers: "<<totalUnique(randomList)<<endl;
    for (int i: randomList) {
        cout << i << ' ';
    }
}
