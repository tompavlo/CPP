#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <map>
using namespace std;

string shiftCipher(const string& text, int move) {
    string result = text;
    for (auto& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = base + (c - base + move + 26) % 26;
        }
    }
    return result;
}

string decryptFrequency(const string& text) {
    vector<int> frequency(26, 0);
    for (char c : text) {
        if (isalpha(c)) {
            frequency[tolower(c) - 'a']++;
        }
    }
    int maxIndex = distance(frequency.begin(), max_element(frequency.begin(), frequency.end()));
    int move = (maxIndex - ('e' - 'a') + 26) % 26;
    return shiftCipher(text, -move);
}

string substituteEncrypt(const string& text, const map<char, char>& key) {
    string encryptedText = text;
    for (char& ch : encryptedText) {
        if (key.count(tolower(ch)) > 0) {
            ch = key.at(tolower(ch));
            if (isupper(ch)) {
                ch = toupper(ch);
            }
        }
    }
    return encryptedText;
}

vector<vector<char>> createVigenereTable() {
    vector<vector<char>> table(26, vector<char>(26));
    for (int row = 0; row < 26; row++) {
        for (int col = 0; col < 26; col++) {
            table[row][col] = 'A' + (row + col) % 26;
        }
    }
    return table;
}

string vigenereEncrypt(const string& text, const string& secret) {
    string encryptedText;
    vector<vector<char>> table = createVigenereTable();
    int keyLength = secret.length();
    int keyIndex = 0;

    for (char plainChar : text) {
        if (isalpha(plainChar)) {
            char keyChar = toupper(secret[keyIndex % keyLength]);
            if (islower(plainChar)) {
                plainChar = toupper(plainChar);
            }

            int row = plainChar - 'A';
            int col = keyChar - 'A';
            char encryptedChar = table[row][col];

            if (islower(text[keyIndex])) {
                encryptedChar = tolower(encryptedChar);
            }

            encryptedText += encryptedChar;
            ++keyIndex;
        } else {
            encryptedText += plainChar;
        }
    }

    return encryptedText;
}

string vigenereDecrypt(const string& encryptedText, const string& secret) {
    string decryptedText;
    vector<vector<char>> table = createVigenereTable();
    int keyLength = secret.length();
    int keyIndex = 0;

    for (char cipherChar : encryptedText) {
        if (isalpha(cipherChar)) {
            char keyChar = toupper(secret[keyIndex % keyLength]);
            if (islower(cipherChar)) {
                cipherChar = toupper(cipherChar);
            }

            int col = keyChar - 'A';
            char decryptedChar = 'A';
            for (int row = 0; row < 26; ++row) {
                if (table[row][col] == cipherChar) {
                    decryptedChar = 'A' + row;
                    break;
                }
            }

            if (islower(encryptedText[keyIndex])) {
                decryptedChar = tolower(decryptedChar);
            }

            decryptedText += decryptedChar;
            ++keyIndex;
        } else {
            decryptedText += cipherChar;
        }
    }

    return decryptedText;
}

void createSquare(char square[5][5]) {
    char startLetter = 'A';
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            char currentLetter = startLetter + (row * 5 + col);
            if (currentLetter > 'J') {
                currentLetter++;
            }
            square[row][col] = currentLetter;
        }
    }
}

string encodePolybius(const string& text, char square[5][5]) {
    string encodedText;

    for (char ch : text) {
        ch = toupper(ch);
        if (isalpha(ch)) {
            for (int row = 0; row < 5; ++row) {
                for (int col = 0; col < 5; ++col) {
                    if (square[row][col] == ch) {
                        encodedText += to_string(row + 1) + to_string(col + 1) + ' ';
                        break;
                    }
                }
            }
        } else {
            encodedText += ' ';
        }
    }

    return encodedText;
}

string decodePolybius(const string& encodedText, char square[5][5]) {
    string decodedText;
    string pair;
    for (char ch : encodedText) {
        if (isdigit(ch)) {
            pair += ch;
        } else if (ch == ' ' && pair.size() == 2) {
            int row = pair[0] - '1';
            int col = pair[1] - '1';
            decodedText += square[row][col];
            pair.clear();
        } else {
            decodedText += ch;
        }
    }
    return decodedText;
}

int main() {
    int option;
    cout << "Select task:\n1) Shift Cipher\n2) Simple Substitution\n3) Vigenere Cipher\n4) Polybius Square\n";
    cin >> option;

    switch (option) {
        case 1: {
            string message;
            cout<<"File or Manually(1 or 2)"<<endl;
            int smth;
            cin>>smth;
            int action, move;
            cout << "Enter message: ";
            cin.ignore();
            getline(cin, message);
            cout << "1) Encrypt\n2) Decrypt\n";
            cin >> action;
            cout << "Enter shift: ";
            cin >> move;
            if (action == 1) {
                cout << shiftCipher(message, move) << endl;
            } else {
                cout << shiftCipher(message, -move) << endl;
            }
            break;
        }
        case 2: {
            string message;
            cout << "Enter message: ";
            cin.ignore();
            getline(cin, message);
            map<char, char> cipherKey;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                cipherKey[ch] = 'z' - (ch - 'a');
            }
            cout << substituteEncrypt(message, cipherKey) << endl;
            break;
        }
        case 3: {
            string message, keyword;
            int action;
            cout << "Enter message: ";
            cin.ignore();
            getline(cin, message);
            cout << "Enter keyword: ";
            cin >> keyword;
            cout << "1) Encrypt\n2) Decrypt\n";
            cin >> action;
            if (action == 1) {
                cout << vigenereEncrypt(message, keyword) << endl;
            } else {
                cout << vigenereDecrypt(message, keyword) << endl;
            }
            break;
        }
        case 4: {
            string message;
            cout<<"Manually or File?(1 or 2)";
            int smth;
            cin>>smth;
            int action;
            cout << "Enter message: ";
            cin.ignore();
            getline(cin, message);
            char square[5][5];
            createSquare(square);
            cout << "1) Encrypt\n2) Decrypt\n";
            cin >> action;
            if (action == 1) {
                cout << encodePolybius(message, square) << endl;
            } else {
                cout << decodePolybius(message, square) << endl;
            }
            break;
        }
        default:
            cout << "Invalid option selected." << endl;
        break;
    }

    return 0;
}