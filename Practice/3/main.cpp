#include <iostream>
#include <map>
using namespace std;
int main() {
    string sentence;
    cout<<"Input some text:";
    getline(cin, sentence);
    map<char, unsigned> letters;
    int counter=0;
    for(char i='a'; i<='z'; i++) {
        for(char j : sentence) {
            if(tolower(j)==i) counter++;
        }
        letters[i]=counter;
        counter=0;
    }
    for (const auto& [letter, times] : letters) {
        cout<<letter<<" - "<<times<<endl;
    }
    return 0;
}
