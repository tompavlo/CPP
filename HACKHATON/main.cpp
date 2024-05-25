#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>


using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    fstream data;
    data.open("210524.txt", ios::in);
    string currline;
    string curWord;
    int curSum=0;
    int counter=0;
    while(getline(data, currline, ';')) {
        stringstream s(currline);
        while(getline(s, curWord, ',')) {
            if(curWord=="T") curSum+=5;
            else if(curWord=="X") curSum++;
            else if(curWord=="CX") curSum++;
            else if(curWord=="S") curSum+=3;
            if(curSum>8) break;
        }
        if(curSum>8) counter++;
        curSum=0;
    }
    auto end = chrono::high_resolution_clock::now();
    long long duration = duration_cast<chrono::milliseconds>(end - start).count();
    cout<<"Counter: "<<counter<<endl;
    cout<<"Duration: "<<duration;
    return 0;
}
