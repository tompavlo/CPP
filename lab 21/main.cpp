#include <climits>
#include <iostream>
#include <iomanip>


using namespace std;

struct Worker {
    string role;
    int employeeID;
    double efficiencyFactor;

    void displayInfo() {
        cout << "\nRole: " << role << "\nID: " << employeeID << "\nEfficiency Factor: " << efficiencyFactor;
    }
};

void drawTable(int warehouseDemand[][3]) {
    cout << endl << setw(5) << "|";
    for (int j = 0; j < 3; j++) {
        cout << setw(4) << " " << "W" << j + 1 << " |";
    }
    cout << endl;
    cout << setw(5) << "|";
    for (int j = 0; j < 3; j++) {
        cout << "-------|";
    }
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << setw(2) << "D" << i + 1 << " |";
        for (int j = 0; j < 3; j++) {
            cout << setw(6) << warehouseDemand[i][j] << " |";
        }
        cout << endl;
        cout << setw(5) << "|";
        for (int j = 0; j < 3; j++) {
            cout << "-------|";
        }
        cout << endl;
    }
}

void distributeByNorthwestCorner(int supply[], int demand[], int costs[][3]) {
    int warehouseDemand[3][3] = {0};
    int supplyIndex = 0, demandIndex = 0, totalCost = 0;

    while (supplyIndex < 3 && demandIndex < 3) {
        int quantity = min(supply[supplyIndex], demand[demandIndex]);
        supply[supplyIndex] -= quantity;
        demand[demandIndex] -= quantity;
        warehouseDemand[supplyIndex][demandIndex] = quantity;
        totalCost += quantity * costs[supplyIndex][demandIndex];
        if (supply[supplyIndex] == 0)
            supplyIndex++;
        if (demand[demandIndex] == 0)
            demandIndex++;
    }
    drawTable(warehouseDemand);
    cout << "Total Cost: " << totalCost;
}

void distributeByMinimumCost(int supply[], int demand[], int costs[][3]) {
    int warehouseDemand[3][3] = {0};
    int totalCost = 0;

    while (true) {
        int minCost = INT_MAX;
        int minSupply = -1, minDemand = -1;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (supply[i] > 0 && demand[j] > 0 && costs[i][j] < minCost) {
                    minCost = costs[i][j];
                    minSupply = i;
                    minDemand = j;
                }
            }
        }
        if (minSupply == -1 || minDemand == -1)
            break;
        int quantity = min(supply[minSupply], demand[minDemand]);
        supply[minSupply] -= quantity;
        demand[minDemand] -= quantity;
        warehouseDemand[minSupply][minDemand] = quantity;
        totalCost += quantity * costs[minSupply][minDemand];
    }

    drawTable(warehouseDemand);
    cout << "Total Cost: " << totalCost;
}

int main() {
    int option;

    cout << "Select a task:\n1) Salary task\n2) Logistic task ";
    cin >> option;

    switch (option) {
        case 1: {
            Worker employees[] = {
                {"Cleaner", 7, 0.5}, {"Nurse", 10, 0.9}, {"Physician", 10, 1.1}, {"Pharmacy Manager", 1, 1.0},
                {"Head of Department", 3, 1.3}, {"Chief Physician", 1, 1.5}, {"Pharmacy Supervisor", 1, 1.2},
                {"Hospital Director", 1, 1.5}
            };
            double totalBudget = 380000;
            float salary;
            int totalEmployees = 0;
            float totalEfficiencyFactor = 0;
            for (int i = 0; i < 8; i++) {
                totalEmployees += employees[i].employeeID;
                totalEfficiencyFactor += employees[i].employeeID * employees[i].efficiencyFactor;
            }

            for (int i = 0; i < 8; i++) {
                salary = (employees[i].employeeID * employees[i].efficiencyFactor / totalEfficiencyFactor) *
                         totalBudget;
                employees[i].displayInfo();
                cout << "\nTotal Salary: " << salary << "\nSalary per Employee: " << salary / employees[i].employeeID;
            }

            break;
        }
        case 2: {
            int supplies[3] = {2000, 1100, 900};
            int demands[3] = {1400, 1600, 1000};
            int costs[3][3] = {{8, 6, 3}, {2, 3, 4}, {6, 1, 5}};
            cout << "Choose an option: \n1) Northwest Corner Method \n2) Minimum Cost Method ";
            cin >> option;
            if (option == 1) distributeByNorthwestCorner(supplies, demands, costs);
            else if (option == 2) distributeByMinimumCost(supplies, demands, costs);
            else cout << "Error";
        }
        default: {
            cout << "Error. Choose 1 or 2\n";
            break;
        }
    }
    return 0;
}
