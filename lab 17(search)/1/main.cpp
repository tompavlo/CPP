#include <iostream>
#include <vector>
using namespace std;

class Student {
public:
    string surname;
    int m1, m2, m3;
    double avgMark = (m1 + m2 + m3) / 3.0;

    Student(string surname, int m1, int m2, int m3) : surname(surname), m1(m1), m2(m2), m3(m3) {
    }
};

void findMaxAvgMark(vector<Student> myStudents) {
    int counter = 0;
    double maxGrade = 0;
    for (Student curStud: myStudents) {
        if (curStud.avgMark > maxGrade) maxGrade = curStud.avgMark;
    }
    for (int i = 0; i < myStudents.size(); i++) {
        if (myStudents[i].avgMark == maxGrade) {
            cout << "Ordinal number of student who have the biggest average grade: " << i + 1 << endl;
            counter++;
        }
    }
    cout << "Total students with max average mark: "<< counter <<  endl;
}

void binarySearch(vector<Student> students, double searchedValue) {
    int low = 0;
    int high = students.size() - 1;
    int mid;
    bool found = false;
    while (low <= high) {
        mid = (low + high) / 2;
        if (students[mid].avgMark == searchedValue) {
            found = true;
            cout << students[mid].surname << " has " << searchedValue << " average mark" << endl;
            int left = mid - 1;
            while (left >= 0 && students[left].avgMark == searchedValue) {
                cout << students[left].surname << " has " << searchedValue << " average mark" << endl;
                left--;
            }

            int right = mid + 1;
            while (right < students.size() && students[right].avgMark == searchedValue) {
                cout << students[right].surname << " has " << searchedValue << " average mark" << endl;
                right++;
            }
            break;
        } if (students[mid].avgMark > searchedValue) {
            low = mid + 1;
        } else high = mid - 1;
    }

    if (!found) cout << "There is no students with such mark" << endl;
}

int main() {
    cout << "Total students: ";
    int size, m1, m2, m3;
    cin >> size;
    string surname;
    vector<Student> myStudents;
    for (int i = 0; i < size; i++) {
        cout << "Insert surname for student: ";
        cin >> surname;
        cout << "Insert mark 1: ";
        cin >> m1;
        cout << "Insert mark 2: ";
        cin >> m2;
        cout << "Insert mark 3: ";
        cin >> m3;
        Student newStudent(surname, m1, m2, m3);
        myStudents.push_back(newStudent);
    }
    findMaxAvgMark(myStudents);
    cout<<"Input mark to find students with: ";
    double searchedValue;
    cin>>searchedValue;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size-1-i; j++) {
            if(myStudents[j].avgMark>myStudents[j+1].avgMark) swap(myStudents[j], myStudents[j+1]);
        }
    }
    binarySearch(myStudents, searchedValue);
    return 0;
}
