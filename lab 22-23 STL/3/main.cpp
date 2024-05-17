#include <iostream>
using namespace std;

class priorityQueue {
public:
    int priority;
    string text;
    priorityQueue *left;
    priorityQueue *right;

    priorityQueue(int p, string t) : priority(p), text(t), left(nullptr), right(nullptr) {
    }
};

void input(priorityQueue *&root, int priority, string text) {
    if (root == nullptr) {
        root = new priorityQueue(priority, text);
    }
    else if (priority < root->priority) {
        input(root->left, priority, text);
    } else {
        input(root->right, priority, text);
    }
}

void showPriority(priorityQueue *&root) {
    if(root==nullptr) return;
    showPriority(root->right);
    cout<<"Priority: "<<root->priority<<endl;
    cout<<"Text: "<<root->text<<endl;
    showPriority(root->left);
}

int main() {
    priorityQueue* root = nullptr;
    input(root, 9, "Leaking data");
    input(root, 8, "Not working app");
    input(root, 10, "Server downtime");
    input(root, 7, "Bug in code");
    input(root, 9, "Slow performance");
    showPriority(root);

    return 0;
}
