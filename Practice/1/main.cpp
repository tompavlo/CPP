#include <iostream>
#include <stack>
using namespace std;
int main() {
    string myWord;    cout<<"Input word:";
    cin>>myWord;

    stack<char> reversedWord;
    for(char i : myWord) {
        reversedWord.push(i);
    }
    while(!reversedWord.empty()) {
        cout << reversedWord.top();
        reversedWord.pop();
    }
}
