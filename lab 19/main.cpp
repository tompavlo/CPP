#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<char> > generatePlayfairKeySquare(const string &cipherKey) {
    vector<vector<char> > keySquare(5, vector<char>(5, '\0'));
    vector<bool> used(26, false);

    int row = 0, col = 0;
    for (char c: cipherKey) {
        c = tolower(c);
        if (!used[c - 'a']) {
            keySquare[row][col] = c;
            used[c - 'a'] = true;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        if (c != 'j' && !used[c - 'a']) {
            keySquare[row][col] = c;
            used[c - 'a'] = true;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    return keySquare;
}

void printKeySquare(const vector<vector<char> > &keySquare) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            cout << keySquare[row][col] << " ";
        }
        cout << endl;
    }
}

void findPositionInKeySquare(const vector<vector<char> > &keySquare, char letter, int &row, int &col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (keySquare[i][j] == letter) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string playfairEncryptDecrypt(const string &inputText, const string &cipherKey, bool encrypt) {
    vector<vector<char> > keySquare = generatePlayfairKeySquare(cipherKey);
    string result;

    for (int i = 0; i < inputText.size(); i += 2) {
        char first = tolower(inputText[i]);
        char second = (i + 1 < inputText.size()) ? tolower(inputText[i + 1]) : 'x';

        int row1 = -1, col1 = -1, row2 = -1, col2 = 1;
        findPositionInKeySquare(keySquare, first, row1, col1);
        findPositionInKeySquare(keySquare, second, row2, col2);

        if (row1 == -1 || col1 == -1 || row2 == -1 || col2 == -1) {
            result += first;
            result += second;
        } else {
            if (row1 == row2) {
                result += keySquare[row1][(col1 + (encrypt ? 1 : -1)) % 5];
                result += keySquare[row2][(col2 + (encrypt ? 1 : -1)) % 5];
            } else if (col1 == col2) {
                result += keySquare[(row1 + (encrypt ? 1 : -1)) % 5][col1];
                result += keySquare[(row2 + (encrypt ? 1 : -1)) % 5][col2];
            } else {
                result += keySquare[row1][col2];
                result += keySquare[row2][col1];
            }
        }
    }
    for (int i = 0; i < inputText.size(); i++)
        if (!islower(inputText[i]))
            result[i] = toupper(result[i]);
    return result;
}

bool is_prime(int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int generatePrimeNumbers(int bits) {
    int p;
    do {
        p = rand() % (1 << bits);
    } while (!is_prime(p));
    return p;
}

int NSD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int nsd = NSD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return nsd;
}

int inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1;
        x1 = t - q * x1;
    }
    if (x0 < 0)
        x0 += m0;
    return x0;
}

int modularExponentiation(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

string RSAEncrypt(int bits, const string &inputText) {
    string encryptedText = "";
    int p, q;
    do {
        p = generatePrimeNumbers(bits);
        q = generatePrimeNumbers(bits);
    } while (p == q);
    int n = p * q;
    int f = (p - 1) * (q - 1);
    int e = 65537;
    int x, y;
    while (NSD(e, f, x, y) != 1 && e < f)
        e++;
    int d = inverse(e, f);
    for (char c: inputText) {
        int m = (int) c;
        int encryptedSymbol = modularExponentiation(m, e, n);
        encryptedText += to_string(encryptedSymbol) + " ";
    }
    return encryptedText;
}

string numbersToString(const std::string &numbers) {
    string result = "";
    stringstream iss(numbers);
    int num;
    while (iss >> num) {
        result += (char) num;
    }

    return result;
}

string RSADecrypt(int bits, const string &text) {
    string decryptedText;
    int p = generatePrimeNumbers(bits);
    int q = generatePrimeNumbers(bits);
    int n = p * q;
    int f = (p - 1) * (q - 1);
    int e = 65537;
    int x, y;
    while (NSD(e, f, x, y) != 1 && e < f)
        e++;
    int d = inverse(e, f);

    istringstream iss(text);
    string token;

    while (std::getline(iss, token, ' ')) {
        if (!token.empty()) {
            int m = stoi(token);
            int decryptedSymbol = modularExponentiation(m, d, n);
            decryptedText += (char) decryptedSymbol;
        }
    }
    return decryptedText;
}

int main() {
    int option;
    string inputText;
    cout << "Choose task:\n1) Playfair Cipher\n2) RSA Encryption/Decryption: ";
    cin >> option;
    switch (option) {
        case 1: {
            string cipherKey;
            cout << "Do you want to use text from a file or your own?\n1) From file\n2) My own: ";
            cin >> option;
            switch (option) {
                case 1: {
                    ifstream file1("Task1.txt");
                    getline(file1, inputText);
                    file1.close();
                    break;
                }
                case 2: {
                    cout << "Type text: ";
                    cin.ignore();
                    getline(cin, inputText);
                    break;
                }
                default: {
                    cout << "Error. Choose 1 or 2" << endl;
                    break;
                }
            }
            cout << "Type keyword: ";
            getline(cin, cipherKey);
            vector<vector<char> > keySquare = generatePlayfairKeySquare(cipherKey);
            cout << "Playfair matrix:\n";
            printKeySquare(keySquare);
            cout << "Choose option: \n1) Encryption\n2) Decryption: ";
            cin >> option;
            switch (option) {
                case 1: {
                    inputText = playfairEncryptDecrypt(inputText, cipherKey, true);
                    break;
                }
                case 2: {
                    inputText = playfairEncryptDecrypt(inputText, cipherKey, false);
                    break;
                }
                default: {
                    cout << "Error. Choose 1 or 2" << endl;
                    break;
                }
            }
            cout << inputText;
            break;
        }
        case 2: {
            int bits;
            cout << "Enter number of bits for RSA key generation: ";
            cin >> bits;
            cout << "Do you want to use text from a file or your own?\n1) From file\n2) My own: ";
            cin >> option;
            switch (option) {
                case 1: {
                    ifstream file1("Task1.txt");
                    getline(file1, inputText);
                    file1.close();
                    break;
                }
                case 2: {
                    cout << "Type text: ";
                    cin.ignore();
                    getline(cin, inputText);
                    break;
                }
                default: {
                    cout << "Error. Choose 1 or 2" << endl;
                    break;
                }
            }
            cout << "Choose option: \n1) Encryption\n2) Decryption: ";
            cin >> option;
            switch (option) {
                case 1: {
                    inputText = RSAEncrypt(bits, inputText);
                    break;
                }
                case 2: {
                    inputText = RSADecrypt(bits, inputText);
                    break;
                }
                default: {
                    cout << "Error. Choose 1 or 2" << endl;
                    break;
                }
            }
            cout << inputText;
            break;
        }
    }


    return 0;
}
