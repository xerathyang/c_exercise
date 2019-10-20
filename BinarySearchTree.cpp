#include <iostream>

using namespace std;

class Node{
    public:
        int keyvalue, leftsize;
        Node *right, *left;
        Node(int);
};

class Tree{
    friend class Node;
    public:
        void insertNode(int);
        void deleteNode(int);
        void searchByValue(int);
        void searchByRank(int);
        void showInorder();
        void showPreorder();
        void showPostorder();
        Node *root;
        Node *curNode = root;
};

Node::Node(int k){
    keyvalue = k;
    leftsize = 1;
    right = left = this;
}

void Tree::insertNode(int a){
    if(root->keyvalue==-1){
        root = new Node(a);
        cout << "[INSERT SUCCESS]" << endl;
    }else{
        if(a==curNode->keyvalue){
            cout << "Duplicate data." << endl;
        }else if(a>curNode->keyvalue){
            curNode = curNode->right;
            
        }
    }

}