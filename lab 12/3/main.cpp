#include <iostream>
#include <list>
using namespace std;

class Car {
public:
    string carName;
    int yearMade;
    int milleage;

    Car(string name, int yearMade, int milleage) : carName(name), yearMade(yearMade), milleage(milleage) {
    }
};

void insertAfter(list<Car> &myList, string carName) {
    for (auto i = myList.begin(); i != myList.end(); ++i) {
        if (i->carName == carName) {
            cout << "Car name: ";
            string carName;
            getline(cin, carName);
            int yearMade;
            cout << "Input year made: ";
            cin >> yearMade;
            int milleage;
            cout << "Milleage: ";
            cin >> milleage;
            Car newCar(carName, yearMade, milleage);
            myList.insert(++i, newCar);
            break;
        }
    }
}

void insertBefore(list<Car> &myList, string carName) {
    for (auto i = myList.begin(); i != myList.end(); ++i) {
        if (i->carName == carName) {
            cout << "Car name: ";
            string carName;
            getline(cin, carName);
            int yearMade;
            cout << "Input year made: ";
            cin >> yearMade;
            int milleage;
            cout << "Milleage: ";
            cin >> milleage;
            Car newCar(carName, yearMade, milleage);
            myList.insert(i, newCar);
            break;
        }
    }
}

bool findByName(const list<Car> &myList, const string &carName) {
    for (auto &i: myList) {
        if (i.carName == carName) return true;
    }
    return false;
}

void deleteByYear(list<Car> &myList, int yearMade) {
    for (auto i = myList.begin(); i != myList.end(); ++i) {
        if (i->yearMade == yearMade) {
            myList.erase(i);
            break;
        }
    }
}

void print(list<Car> myList) {
    for (auto i: myList) {
        cout << "Car name: " << i.carName << endl;
        cout << "Year made: " << i.yearMade << endl;
        cout << "Milleage: " << i.milleage << endl;
    }
}

void printMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "|                       MENU                      |" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "|1.Input element at the start.                    |" << endl;
    cout << "|2.Input element at the end                       |" << endl;
    cout << "|3.Input element after the value.                 |" << endl;
    cout << "|4.Input element before the value.                |" << endl;
    cout << "|5.Find node by car name.                         |" << endl;
    cout << "|6.Delete node by year made.                      |" << endl;
    cout << "|7.Print list.                                    |" << endl;
    cout << "|8.Exit.                                          |" << endl;
    cout << "---------------------------------------------------" << endl;
}

using namespace std;

int main() {
    list<Car> cars;
    int navig;
    string name;
    int yearMade, milleage;
    printMenu();
    cin >> navig;
    cin.ignore();
    while (navig != 8) {
        switch (navig) {
            case 1: {
                cout << "Input car name" << endl;
                getline(cin, name);
                cout << "Input year made" << endl;
                cin >> yearMade;
                cout << "Milleage(in km)" << endl;
                cin >> milleage;
                Car myCar(name, yearMade, milleage);
                cars.push_front(myCar);
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            }
            case 2: {
                cout << "Input car name" << endl;
                getline(cin, name);
                cout << "Input year made" << endl;
                cin >> yearMade;
                cout << "Milleage(in km)" << endl;
                cin >> milleage;
                Car myCa(name, yearMade, milleage);
                cars.push_back(myCa);
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            }
            case 3: {
                cout << "Input name for the car to input afer: ";
                string carToFind;
                getline(cin, carToFind);
                insertAfter(cars, carToFind);
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            }
            case 4: {
                cout << "Input name for the car to input before: ";
                string carToFind2;
                getline(cin, carToFind2);
                insertBefore(cars, carToFind2);
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            }
            case 5: {
                cout << "Input name for car to find: ";
                string carFind;
                getline(cin, carFind);
                if (findByName(cars, carFind)) cout << "There is car with name " << carFind;
                else cout << "There is no such car with name " << carFind;
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            }
            case 6: {
                cout << "Year car's to delete: ";
                int yearDel;
                cin >> yearDel;
                deleteByYear(cars, yearDel);
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            }
            case 7:
                print(cars);
                system("cmd.exe /c pause");
                system("cmd.exe /c cls");
                printMenu();
                cin >> navig;
                cin.ignore();
                break;
            case 8:
                break;
            default:
                cout << "Wrong input" << endl;
                cin >> navig;
                cin.ignore();
                break;
        }
    }
}
