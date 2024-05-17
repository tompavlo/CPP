#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
using namespace std;

int countName(vector<string> list, string nameToFind) {
    int counter=0;
    for(string name : list) {
        if(name==nameToFind) counter++;
    }
    return counter;
}

int main() {
    fstream data;
    data.open("data.txt", ios::in);
    vector<string> words;
    string word;
    while(data>>word) {
        words.push_back(word);
    }
    cout<<"Input name to find: ";
    string name;
    cin>>name;
    cout<<"Number of this name in list: "<<countName(words, name)<<endl;
    for(int i=0; i<words.size(); i++) {
        transform(words[i].begin(), words[i].end(), words[i].begin(), ::toupper);
    }
    for(string s : words) {
        cout<<s<<' ';
    }
    for(int i=0; i<words.size(); i++) {
        transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
    }
    cout<<endl;
    for(string s : words) {
        cout<<s<<' ';
    }
    cout<<endl;
    char vowels[]{'a','e','y','u','i','o'};
    int cp=0;
    for(int i=0; i<words.size(); i++) {
        for(int j=0; j<6; j++) {
            if(words[i].starts_with(vowels[j])) {
                swap(words[i], words[cp]);
                cp++;
            }
        }
    }
    for(string s : words) {
        cout<<s<<' ';
    }
    return 0;
}
