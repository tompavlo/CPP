#include <iostream>
using namespace std;

struct tree {
    double temperature;
    int hour;
    string model;
    string district;
    tree *left;
    tree *right;
} *start = nullptr;

void add(double temperature, int hour, string model, string district) {
    tree *curTree = new tree;
    curTree->temperature = temperature;
    curTree->hour = hour;
    curTree->model = model;
    curTree->district = district;
    curTree->left = nullptr;
    curTree->right = nullptr;
    if (start == nullptr) {
        start = curTree;
    } else {
        tree *manip = start;
        while (manip != nullptr) {
            if (temperature < manip->temperature) {
                if (manip->left == nullptr) {
                    manip->left = curTree;
                    break;
                }
                manip = manip->left;
            } else {
                if (manip->right == nullptr) {
                    manip->right = curTree;
                    break;
                }
                manip = manip->right;
            }
        }
    }
}

void prinTree(tree *root) {
    if (root == nullptr) return;
    prinTree(root->left);
    cout << root->temperature << endl;
    prinTree(root->right);
}

double avgTemp(tree *root, double &sum, int &counter, string district) {
    if (root == nullptr) return 0;
    avgTemp(root->left, sum, counter, district);
    if (root->district == district) {
        sum += root->temperature;
        counter++;
    }
    avgTemp(root->right, sum, counter, district);
    return sum / counter;
}

double maxTemp(tree *root, double &max, string model) {
    if (root == nullptr) return 0;
    maxTemp(root->left, max, model);
    if (root->model == model) {
        if (root->temperature > max) max = root->temperature;
    }
    maxTemp(root->right, max, model);
    return max;
}

double minTemp(tree *root, double &min, string model) {
    if (root == nullptr) return 0;
    minTemp(root->left, min, model);
    if (root->model == model) {
        if (root->temperature < min) min = root->temperature;
    }
    minTemp(root->right, min, model);
    return min;
}

double avgTempByHour(tree *root, double &sum, int &counter, int from, int to) {
    if (root == nullptr) return 0;
    avgTempByHour(root->left, sum, counter, from, to);
    if (root->hour >= from && root->hour <= to) {
        sum += root->temperature;
        counter++;
    }
    avgTempByHour(root->right, sum, counter, from, to);
    return sum / counter;
}
void deleting(tree *root) {
    if (root == nullptr) return;
    deleting(root->left);
    delete root;
    deleting(root->right);
}

int main() {
    add(23, 20, "ANALOG", "SCHEVA");
    add(15, 10, "ANALOG", "SCHEVA");
    add(3, 16, "ANALOG", "SCHEVA");
    add(28, 9, "ANALOG", "SCHEVA");
    add(10, 15, "DIGITAL", "BUKOVINA");
    add(2, 21, "DIGITAL", "BUKOVINA");
    add(6, 5, "DIGITAL", "BUKOVINA");
    add(29, 17, "DIGITAL", "BUKOVINA");
    add(9, 11, "DIGITAL", "TRAVNEVIY");
    add(22, 19, "DIGITAL", "TRAVNEVIY");
    add(5, 15, "ANALOG", "TRAVNEVIY");
    add(21, 12, "ANALOG", "TRAVNEVIY");
    double sum = 0;
    int counter = 0;
    cout << "Avg temp of SCHEVCHEKO district: " << avgTemp(start, sum, counter, "SCHEVA") << endl;
    sum = 0;
    counter = 0;
    cout << "Avg temp of BUKOVINSKIY district: " << avgTemp(start, sum, counter, "BUKOVINA") << endl;
    sum = 0;
    counter = 0;
    cout << "Avg temp of PERSOTRAVNEVIY district: " << avgTemp(start, sum, counter, "TRAVNEVIY") << endl;
    double max = start->temperature;
    cout << "Max temp of ANALOG termometer is: " << maxTemp(start, max, "ANALOG") << endl;
    max = start->temperature;
    cout << "Max temp of DIGITAL termometer is: " << maxTemp(start, max, "DIGITAL") << endl;
    cout << "Min temp of ANALOG termometer is: " << minTemp(start, max, "ANALOG") << endl;
    max = start->temperature;
    cout << "Min temp of DIGITAL termometer is: " << minTemp(start, max, "DIGITAL") << endl;
    sum = 0;
    counter = 0;
    cout << "AVG temp in the afternoon: "<<avgTempByHour(start, sum, counter, 12, 16);
    deleting(start);
}
