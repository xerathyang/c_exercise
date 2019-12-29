#include <iostream>

using namespace std;

class twothreeTree;

class Node{
    friend class twothreeTree;
    private:
        Node *left;
        Node *middle1;
        Node *middle2;
        Node *right;
        Node *parent;
        int data1,data2;
        Node(int,int);
};

Node::Node(int num1,int num2){
    data1 = num1;
    data2 = num2;
    left = right = middle1 = middle2 = parent = nullptr;
}

class twothreeTree{
    private:
        Node *root;
    public:
        void insert(int);
        void insertnode(Node*,int);
        void promotion(Node*,int);
        void print(Node*);
};

void twothreeTree::insert(int num){
    if(root==nullptr){
        root = new Node(num, 0);
    }else{
        insertnode(root, num);
    }
}

void twothreeTree::insertnode(Node* node,int num){
    if(num<node->data1){//left
        if(node->left!=nullptr){//if ptr valid
            insertnode(node->left, num);//move to next node
        }else if(node->data2==0){//data2 is empty
            node->data2 = node->data1;//data1 to data2
            node->data1 = num;//put data1
        }else{//has two data
            promotion(node, num);
        }
    }else if(node->data2!=0&&num>node->data2){//right
        if(node->right!=nullptr){
            insertnode(node->right, num);
        }else{
            promotion(node, num);
        }
    }else{
        if(node->middle1!=nullptr){//middle
            insertnode(node->middle1, num);
        }else{
            promotion(node, num);
        }
    }
}

void twothreeTree::promotion(Node* node, int num){
    if(num<node->data1){//left
        if(node->parent==nullptr){
            
        }
    }else if(num>node->data1&&num<node->data2){//middle

    }else{//right

    }
}

void twothreeTree::print(Node* node){
}

int main(){

}