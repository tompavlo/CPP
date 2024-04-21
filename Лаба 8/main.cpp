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
    if(root==nullptr) return;
    prinTree(root->left);
    cout<<root->temperature<<endl;
    prinTree(root->right);

}
double avgTemp(tree *root, double& sum, int& counter) {
    if(root==nullptr) return 0;
    avgTemp(root->left,sum, counter);
    sum+=root->temperature;
    counter++;
    avgTemp(root->right, sum, counter);
    return sum/counter;
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
    double sum=0;
    int counter=0;
    cout<<"Avg temp: "<<avgTemp(start, sum, counter);

    return 0;
}
