#include <iostream>
#include <map>
using namespace std;

class PhoneBook {
public:
    map<string, string> phoneBook;

    void addNumber() {
        cout << "Input name for contact: ";
        string name;
        getline(cin >> ws, name);
        cout << "Input number for contact: ";
        string number;
        cin >> number;
        phoneBook[name] = number;
    }

    void show() {
        for (const auto &[name, number]: phoneBook) {
            cout << name << ' ' << number << endl;
        }
    }

    void deleteByName() {
        cout << "Insert name of contact to delete: ";
        string toDel;
        getline(cin >> ws, toDel);
        if (!phoneBook.contains(toDel)) {
            cout << "There is no such contact";
            return;
        }
        phoneBook.erase(toDel);
    }
    void showNumbByName() {
        cout<<"Contact's name: ";
        string name;
        getline(cin >> ws,name);
        if(!phoneBook.contains(name)) {
            cout<<"There is no such adress";
            return;
        }
        cout<<name<<": "<<phoneBook[name]<<endl;
    }

};

int main() {
    cout<<"Phone book simulator"<<endl;
    PhoneBook myBook;
    myBook.addNumber();
    myBook.addNumber();
    myBook.addNumber();
    myBook.show();
    myBook.deleteByName();
    myBook.show();
    myBook.showNumbByName();
}
