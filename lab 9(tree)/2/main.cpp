#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

struct tree {
    int number;
    string name;
    int price;
    tree *right;
    tree *left;
};

tree *createNode(int number, string name, int price) {
    tree *newNode = new tree;
    newNode->number = number;
    newNode->name = name;
    newNode->price = price;
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}

void insert(tree *&root, int number, string name, int price) {
    if (!root) root = createNode(number, name, price);
    else if (number < root->number) insert(root->left, number, name, price);
    else insert(root->right, number, name, price);
}

void deleteTree(tree *&root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int findTotalNodes(tree *&root) {
    if (root == nullptr) return 0;
    return 1 + findTotalNodes(root->left) + findTotalNodes(root->right);
}

int findTotalPrice(tree *&root) {
    if (root == nullptr) return 0;
    return root->price + findTotalPrice(root->left) + findTotalPrice(root->right);
}

double findAvgPrice(tree *&root) {
    if (!root) return 0;
    int sum = findTotalPrice(root);
    int counter = findTotalNodes(root);
    return static_cast<double>(sum) / counter;
}

void deleteByNumber(tree *&root, int number) {
    if (!root) return;
    if (number == root->number) {
        deleteTree(root);
        root=nullptr;
    } else {
        deleteByNumber(root->left, number);
        deleteByNumber(root->right, number);
    }
}

void countNodesAtLevels(tree* root) {
    if (root==nullptr) return;
    queue<tree*> q;
    q.push(root);
    int counter=1;
    while (!q.empty()) {
        cout<<"Nodes at level "<<counter<<" - "<<q.size()<<endl;
        for(int i=0; i<q.size(); i++){
            tree* current = q.front();
            q.pop();
            if(current->left!=nullptr) {
                q.push(current->left);
            }
            if(current->right!=nullptr) {
                q.push(current->right);
            }
        }
        counter++;
    }
}

void prinTree(tree* root) {
    if(root==nullptr) return;
    prinTree(root->left);
    cout<<"Unique code: "<<root->number<<endl;
    cout<<"Name: "<<root->name<<endl;
    cout<<"Price: "<<root->price<<endl;
    prinTree(root->right);

}

int main() {
    fstream data;
    tree *root = nullptr;
    data.open("data.csv", ios::in);
    string line, name, temp;
    int number, price;
    getline(data, line);
    while(getline(data, line)) {
        stringstream s(line);
        getline(s, temp, ';');
        number=atoi(temp.c_str());
        getline(s, name, ';');
        getline(s, temp);
        price=atoi(temp.c_str());
        insert(root, number, name, price);
    }
    data.close();
    prinTree(root);
    cout << "AVG price: " << findAvgPrice(root)<<endl;
    countNodesAtLevels(root);
    cout<<"Number of techic to delete: ";
    cin>>number;
    deleteByNumber(root, number);
    prinTree(root);
    deleteTree(root);

}
