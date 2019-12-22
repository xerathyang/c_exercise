#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

Node::Node() {
    left = right = this;
}

class AVLTree {
private:
    Node* root;
public:
    AVLTree();
    void insert(int);
    void remove();
    void print();
};

AVLTree::AVLTree() {
    root->left = root->right = root;
}

void AVLTree::insert(int num) {
    Node* curNode = root;
    if (root->left == root && root->right == root) {
        root->data = num;
        return;
    }
    while (num != curNode->data) {
        if (num == root->data)
            return;
        if (num > root->data)
            curNode = root->right;
        else
            curNode = root->left;

    }
    
    
}

int main()
{
    std::cout << "Hello World!\n";
}

