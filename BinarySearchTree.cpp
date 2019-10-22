#include <iostream>

using namespace std;

class Node{
    public:
        int keyvalue, leftsize;
        Node *right, *left,*parent;
        Node(int);
};

class Tree{
    friend class Node;
    public:
        void insertNode(int);
        void deleteNode(int);
        bool searchByValue(int,int);
        void searchByRank(int);
        void showInorder();
        void showPreorder();
        void showPostorder();
    private:
        Node *root=new Node(0);
};

Node::Node(int k){
    keyvalue = k;
    leftsize = 1;
    parent = NULL;
    right = left = NULL;
}

void Tree::insertNode(int a){
    Node *prevNode = 0;
    Node *currNode = this->root;
    Node *insert = new Node(a);

    if(searchByValue(a,0)==1){
        cout << "Duplicate data." << endl;
        return void();
    }

    if(currNode->keyvalue==0){
        this->root = insert;
        cout << "[INSERT SUCCESS]" << endl;
        return void();
    }

    while(currNode!=NULL){
        prevNode = currNode;
        if(a<currNode->keyvalue){
            currNode->leftsize++;
            currNode = currNode->left;
        }else{
            currNode = currNode->right;
        }
    }

    insert->parent = prevNode;

    if(a<prevNode->keyvalue){
        prevNode->left = insert;
    }else{
        prevNode->right = insert;
    }  
    cout << "[INSERT SUCCESS]" << endl;
}

void Tree::deleteNode(int a){
    Node *curNode = this->root;
    if(searchByValue(a,0)==0){
        cout << "No such value to delete." << endl;
    }else{
        while(curNode->keyvalue!=a){
            if(a<curNode->keyvalue){
                curNode = curNode->left;
            }else{
                curNode = curNode->right;
            }
        }
        if(curNode->left==NULL){

        }else if(curNode->right==NULL){
            
        }
    }
}

bool Tree::searchByValue(int a,int v){
    int depth=1;
    Node *curNode = this->root;
    while(a!=curNode->keyvalue){
        if((curNode->left==NULL&&curNode->right==NULL)
            ||(curNode->left==curNode&&curNode->right==curNode)){
            if(v==1){
                cout << "No such value." << endl;
            }
            return 0;
        }
        if(a<curNode->keyvalue){
            curNode = curNode->left;
        }else if(a>curNode->keyvalue){
            curNode = curNode->right;
        }
        if(curNode==NULL){
            if(v==1){
                cout << "No such value." << endl;
            }
            return 0;
        }
        depth++;
    }
    if(v==1){
        cout << "LeftSize = " << curNode->leftsize << ", Depth = "
            << depth << endl;
    }
    return 1;
}

int main(){
    int input,var;
    Tree a;
    while(cin>>input){
        switch(input){
            case 1:
                cin >> var;
                a.insertNode(var);
                break;
            case 2:
                cin >> var;
                a.deleteNode(var);
                break;
            case 3:
                cin >> var;
                a.searchByValue(var,1);
                break;
            }
    }
}