#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

int directSearch(vector<string> text, string wordToFind) {
    int cp=0;
    int counter = 0;
    for(auto word : text) {
        int wordSize=word.size();
        if(!isalpha(word[wordSize-1])) wordSize--;
        if(wordSize!=wordToFind.size()) continue;
        for(int i=0; i<wordSize; i++) {
            if(word[i]==wordToFind[cp]) {
                cp++;
            }
            else cp=0;
            if(cp==wordToFind.size()) {
                counter++;
                cp=0;
                break;
            }
        }
    }
    if(counter==0) return -1;
    return counter;
}

void computeLPSArray(string pattern, vector<int> &lps) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    int M = pattern.size();
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(vector<string> text, string wordToFind) {
    int M = wordToFind.size();
    int count = 0;
    vector<int> lps(M);
    computeLPSArray(wordToFind, lps);
    for ( auto word : text) {
        int N = word.size();
        int j = 0;
        for (int i = 0; i < N; i++) {
            if (!isalpha(word[i])) continue;
            while (j > 0 && word[i] != wordToFind[j]) {
                j = lps[j - 1];
            }
            if (word[i] == wordToFind[j]) {
                j++;
            }
            if (j == M) {
                count++;
                j = lps[j - 1];
            }
        }
    }
    return count > 0 ? count : -1;
}

int BoyerMooreSearch(vector<string> text, string wordToFind) {
    int m = wordToFind.size();
    unordered_map<char, int> badChar;

    int count = 0;

    for (auto word : text) {
        int n = word.size();
        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && word[s + j] == wordToFind[j])
                j--;

            if (j < 0) {
                count++;
                s += (s + m < n) ? m - badChar[word[s + m]] : 1;
            } else {
                s += max(1, j - badChar[word[s + j]]);
            }
        }
    }

    return count > 0 ? count : -1;
}

int main() {
    fstream text;
    text.open("text.txt", ios::in);
    cout<<"Word to find: ";
    string wordToFind;
    cin>>wordToFind;
    string curWord;
    vector<string> esse;
    while(text>>curWord) {
        esse.push_back(curWord);
    }

    cout<<"Times your word was in text(direct search(modified)): "<<directSearch(esse, wordToFind)<<endl;
    cout<<"Times your word was in text(KMP search): "<<KMPSearch(esse, wordToFind)<<endl;
    cout<<"Times your word was in text(Boyer-Moore search): "<<BoyerMooreSearch(esse, wordToFind)<<endl;
    return 0;
}
