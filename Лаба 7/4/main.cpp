#include <iostream>
using namespace std;

struct queue {
    string teamName;
    string city;
    int points;
    queue *next;
} *first{}, *last{};

void addQueue(string const &teamName, string const &city, int const points) {
    queue *newTeam = new queue;
    newTeam->teamName = teamName;
    newTeam->city = city;
    newTeam->points = points;
    if (last == nullptr) {
        last = newTeam;
        first = newTeam;
        newTeam->next = nullptr;
    } else {
        last->next = newTeam;
        newTeam->next = nullptr;
        last = newTeam;
    }
}

void findLeader() {
    queue *leader = first;
    for (queue *manip = first->next; manip != nullptr; manip = manip->next) {
        if (manip->points > leader->points) leader = manip;
    }
    cout << "Leader is: " << leader->teamName << endl;
    cout << "Points: " << leader->points << endl;
}

void findOutsider() {
    queue *outsier = first;
    for (queue *manip = first->next; manip != nullptr; manip = manip->next) {
        if (manip->points < outsier->points) outsier = manip;
    }
    cout << "Outsider is: " << outsier->teamName << endl;
    cout << "Points: " << outsier->points;
}

void findSameCity() {
    cout << endl;
    for (queue *manip1 = first; manip1 != nullptr; manip1 = manip1->next) {
        bool wasTheSame = false;
        for (queue *findSameMainCycle = first; findSameMainCycle != manip1;
             findSameMainCycle = findSameMainCycle->next) {
            if (findSameMainCycle->city == manip1->city) {
                wasTheSame = true;
                break;
            }
        }
        if (!wasTheSame) {
            cout << "City: " << manip1->city << endl;
            cout << "Team: " << manip1->teamName << endl;
        }
        for (queue *manip2 = first; manip2 != nullptr; manip2 = manip2->next) {
            if (wasTheSame) break;
            if (manip2 != manip1 && manip2->city == manip1->city) cout << "Team: " << manip2->teamName << endl;
        }
    }
}

int main() {
    string teamName;
    string city;
    int points;
    while (true) {
        cout << "Input team name(or done to stop):";
        getline(cin, teamName);
        if (teamName == "done") break;
        cout << "Input city where it's team from:";
        getline(cin, city);
        cout << "Input points:";
        cin >> points;
        addQueue(teamName, city, points);
        cin.ignore();
    }
    findLeader();
    findOutsider();
    findSameCity();
}
