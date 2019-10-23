#include <iostream>

using namespace std;

class Node{
    public:
        int keyvalue;
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
        void rankfind(Node *,int);
        void showInorder();
        void inorder(Node*);
        void showPreorder();
        void preorder(Node *);
        void showPostorder();
        void postorder(Node *);
        void leftsize(Node *);
        int index,hasrank,size;

    private:
        Node *root=new Node(0);
};

Node::Node(int k){
    keyvalue = k;
    parent = this;
    right = left = NULL;
}

void Tree::insertNode(int a){
    Node *prevNode = 0;
    Node *currNode = this->root;
    Node *insert = new Node(a);

    if(searchByValue(a,0)==1){
        cout << "Duplicate data." << endl;
        return;
    }

    if(currNode->keyvalue==0){
        this->root = insert;
        cout << "[INSERT SUCCESS]" << endl;
        return;
    }

    while(currNode!=NULL){
        prevNode = currNode;
        if(a<currNode->keyvalue){
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
    return;
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
        if(curNode->parent==curNode){
            if(curNode->left==NULL&&curNode->right==NULL){
                curNode->keyvalue = 0;
            }else if(curNode->right==NULL&&curNode->left!=NULL){
                this->root = curNode->left;
            }else if(curNode->right!=NULL&&curNode->left==NULL){
                this->root = curNode->right;
            }else{
                Node *tmp=curNode->right;
                while(tmp->left!=NULL){
                    tmp = tmp->left;
                }
                if(tmp->parent->right==tmp){
                    tmp->parent->right = tmp->right;
                }else{
                    tmp->parent->left = tmp->right;
                }
                tmp->right = curNode->right;
                tmp->left = curNode->left;
                this->root = tmp;
            }
        }else if(curNode->left==NULL&&curNode->right==NULL){
            if(curNode->keyvalue>curNode->parent->keyvalue){
                curNode->parent->right = NULL;
            }else{
                curNode->parent->left = NULL;
            }
        }else if(curNode->right==NULL&&curNode->left!=NULL){
            if(curNode->keyvalue>curNode->parent->keyvalue){
                curNode->parent->right = curNode->left;
            }else{
                curNode->parent->left = curNode->left;
            }
        }else if(curNode->right!=NULL&&curNode->left==NULL){
            if(curNode->keyvalue>curNode->parent->keyvalue){
                curNode->parent->right = curNode->right;
            }else{
                curNode->parent->left = curNode->right;
            }
        }else{
            
            Node *tmp=curNode->right;
            while(tmp->left!=NULL){
                tmp = tmp->left;
            }
            if(tmp->parent->right==tmp){
                tmp->parent->right = tmp->right;
            }else{
                tmp->parent->left = tmp->right;
            }
            tmp->right = curNode->right;
            tmp->left = curNode->left;
            if(curNode->keyvalue>curNode->parent->keyvalue){
                curNode->parent->right = tmp;
            }else{
                curNode->parent->left = tmp;
            }
        }
        cout << "[DELETE SUCCESS]" << endl;
    }
    return;
}

bool Tree::searchByValue(int a,int v){
    int depth = 1;
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
    this->size = 1;
    leftsize(curNode->left);
    if(v==1){
        cout << "LeftSize = " << this->size << ", Depth = "
            << depth << endl;
    }
    return 1;
}

void Tree::leftsize(Node* curNode){
    if(curNode){
        leftsize(curNode->left);
        this->size++;
        leftsize(curNode->right);
    }
    return;
}

void Tree::searchByRank(int a){
    Node *curNode=this->root;
    if(curNode->keyvalue==0){
        cout << "No such value." << endl;
        return;
    }
    this->index = 0;
    this->hasrank = 0;
    rankfind(curNode, a);
    if(this->hasrank==0)
        cout << "No such value." << endl;
    return;
}

void Tree::rankfind(Node* curNode,int a){
    if(curNode==NULL)
        return;
    rankfind(curNode->left,a);
    if(++index==a){
        cout << "The " << a << "th smallest is " << curNode->keyvalue << endl;
        this->hasrank = 1;
        return;
    }
    rankfind(curNode->right, a);
    return;
}

void Tree::showInorder(){
    inorder(this->root);
    cout << endl;
    return;
}

void Tree::inorder(Node* curNode){
    if(curNode){
        inorder(curNode->left);
        cout << curNode->keyvalue << " ";
        inorder(curNode->right);
    }
    return;
}

void Tree::showPostorder(){
    postorder(this->root);
    cout << endl;
    return;
}

void Tree::postorder(Node* curNode){
    if(curNode){
        postorder(curNode->left);
        postorder(curNode->right);
        cout << curNode->keyvalue << " ";
    }
    return;
}

void Tree::showPreorder(){
    preorder(this->root);
    cout << endl;
    return;
}

void Tree::preorder(Node* curNode){
    if(curNode){
        cout << curNode->keyvalue << " ";
        preorder(curNode->left);
        preorder(curNode->right);
    }
    return;
}

int main(){
    int input=0;
    int var = 0;
    Tree a;
    while(cin>>input){
        var = 0;
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
            case 4:
                cin >> var;
                a.searchByRank(var);
                break;
            case 5:
                a.showInorder();
                break;
            case 6:
                a.showPreorder();
                break;
            case 7:
                a.showPostorder();
                break;
            default:
                break;
            }
    }
}