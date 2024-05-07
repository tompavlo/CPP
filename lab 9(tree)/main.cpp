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

void inputResurcivly(tree *&node, int data) {
    if (!node) node = createNode(data);
    else if (data < node->key) inputResurcivly(node->left, data);
    else inputResurcivly(node->right, data);
}

bool checkForTheSameValue(tree *&root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    return checkForTheSameValue(root->left, key) || checkForTheSameValue(root->right, key);
}

void createNodes(int size, bool manually) {
    if (manually) {
        cout << "Input data" << endl;
        for (int i = 0; i < size; i++) {
            int data;
            cin >> data;
            while (checkForTheSameValue(root, data)) {
                cout << "There is already in tree this key, input again\n";
                cin >> data;
            }
            inputResurcivly(root, data);
        }
    } else {
        cout << "Input diapazon: ";
        int start, end;
        cin >> start >> end;
        if (start > end) swap(start, end);
        while (size > end - start + 1) {
            cout << "Incorect diapazon, input again: ";
            cin >> start >> end;
            if (start > end) swap(start, end);
        }
        for (int i = 0; i < size; i++) {
            int data = rand() % (end - start + 1) + start;
            while (checkForTheSameValue(root, data)) {
                data = rand() % (end - start + 1) + start;
            }
            inputResurcivly(root, data);
        }
    }
}

void createEvenAndNotEvenTrees(tree *mainRoot, tree*&rootEven, tree *&rootNotEven) {
    if (!mainRoot) return;
    if (mainRoot->key % 2 == 0) inputResurcivly(rootEven, mainRoot->key);
    else inputResurcivly(rootNotEven, mainRoot->key);
    createEvenAndNotEvenTrees(mainRoot->left, rootEven, rootNotEven);
    createEvenAndNotEvenTrees(mainRoot->right, rootEven, rootNotEven);
}

void printTree(tree *root) {
    if (!root) return;
    printTree(root->left);
    cout << root->key << ' ';
    printTree(root->right);
}

int depthOfTree(tree *root) {
    if (root==nullptr) return 0;
    return 1 + max(depthOfTree(root->left), depthOfTree(root->right));
}

void deleteTree(tree*& root) {
    if(!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int main() {
    cout << "Total nodes: ";
    int size;
    cin >> size;
    cout << "Input mannualy?" << endl;
    bool man;
    cin >> man;
    srand(time(nullptr));
    createNodes(size, man);
    printTree(root);
    tree *even = nullptr, *notEven = nullptr;
    createEvenAndNotEvenTrees(root, even, notEven);
    cout << endl;
    printTree(even);
    cout << endl;
    printTree(notEven);
    cout<<"\nDepth of main tree: "<<depthOfTree(root)<<endl;
    cout<<"Depth of even tree: "<<depthOfTree(even)<<endl;
    cout<<"Depth of not even tree: "<<depthOfTree(notEven)<<endl;
    deleteTree(root);
    deleteTree(notEven);
    deleteTree(even);
}
