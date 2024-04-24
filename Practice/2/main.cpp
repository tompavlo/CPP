#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;
int main() {
    cout<<"Total clients: ";
    int size;
    cin>>size;
    queue<int> clients;
    for(int i=1; i<size; i++) {
        clients.push(i);
    }
    while(!clients.empty()) {
        cout<<"Було обслуговано клієнта №"<<clients.front()<<endl;
        clients.pop();
        this_thread::sleep_for(chrono::seconds(1));
    }
    return 0;
}
