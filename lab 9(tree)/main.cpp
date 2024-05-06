#include <iostream>
using namespace std;
struct tree {
    int key;
    tree *left;
    tree *right;
} *root;

tree *createNode(int data) {
    tree *newNode = new tree;
    newNode->key = data;
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}

void input(int data) {
    tree *newNode = createNode(data);
    if (root == nullptr) root = newNode;
    else {
        tree *manip = root;
        while (manip != nullptr) {
            if (newNode->key >= manip->key) {
                if (manip->right == nullptr) {
                    manip->right = newNode;
                    break;
                }
                manip = manip->right;
            } else {
                if (manip->left == nullptr) {
                    manip->left = newNode;
                    break;
                }
                manip = manip->left;
            }
        }
    }
}
void inputResurcivly(tree*& node, int data) {
    if(!node) {
        node = createNode(data);
    }
    else if (data< node->key) {
        inputResurcivly(node->left, data);
    }
    else inputResurcivly(node->right, data);
}

void printTree(tree *root) {
    if(!root) return;
    printTree(root->left);
    cout<<root->key<<' ';
    printTree(root->right);

}

int main() {
    inputResurcivly(root, 1);
    inputResurcivly(root, 16);
    inputResurcivly(root, 1);
    inputResurcivly(root, 17);
    inputResurcivly(root, 6);
    inputResurcivly(root, 3);
    inputResurcivly(root, 18);
    inputResurcivly(root, 5);
    printTree(root);
}
