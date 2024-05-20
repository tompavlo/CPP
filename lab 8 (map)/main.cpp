#include <iostream>
#include <map>

using namespace std;

void appPair(map<string, int>& thisMap, string key, int value) {
    thisMap.emplace(key, value);
}

void deleteByKey(map<string, int>& thisMap, string key) {
    if(!thisMap.contains(key)) {
        cout<<"There is no such key"<<endl;
        return;
    }
    thisMap.erase(key);
}

void findByKey(map<string, int>& thisMap, string key) {
    if(!thisMap.contains(key)) {
        cout<<"There is no such key"<<endl;
        return;
    }
    cout<<thisMap.at(key)<<endl;
}

int containsByKey(map<string, int>& thisMap, string key) {
    if(!thisMap.contains(key)) return -1;
    return 1;
}

bool checkIsThereKey(map<string, int>& thisMap, string key) {
    return thisMap.contains(key);
}

void printMap(map<string, int>& thisMap) {
    for(auto & i : thisMap) {
        cout<<i.first<<" - "<<i.second<<endl;
    }
}

void merge(map<string, int>& thisMap, map<string, int>& secondMap) {
    thisMap.merge(secondMap);
}
int main() {
    map<string, int> myMap;
    appPair(myMap, "apples", 89);
    findByKey(myMap, "apples");
    appPair(myMap, "peach", 50);
    printMap(myMap);
    deleteByKey(myMap, "apples");
    cout<<containsByKey(myMap, "y")<<endl;
    cout<<boolalpha<<checkIsThereKey(myMap, "apples")<<endl;
    appPair(myMap, "strawberry", 50);
    map<string, int> drinks;
    appPair(drinks, "Orange juice", 70);
    merge(myMap, drinks);
    printMap(myMap);
    return 0;
}
