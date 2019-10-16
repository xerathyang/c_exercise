#include <iostream>

using namespace std;

struct triple{
    int row, col, value;
};

class Matrix;
class Node{
    friend class Matrix;
    friend istream &operator>>(istream &is, Matrix &m);
    friend ostream &operator<<(ostream &, const Matrix &);
    private:
        Node *down, *right; //to next node
        bool head;  //is header?
        union{
            Node *next; //for header node
            triple Triple;  //for element node
        };
        Node(bool, triple *);
};

Node::Node(bool b, triple *t){
    head = b;   //is header?
    if(b){
        down = right = this;    //header
    }else
        Triple = *t;    //element
};

class Matrix{
    friend istream &operator>>(istream &, Matrix &);
    friend ostream &operator<<(ostream &, const Matrix &);
    public:
        Matrix(const Matrix &a);
        const Matrix &operator=(const Matrix &a);
        ~Matrix();
        Matrix operator+(const Matrix &b);
        Matrix operator-(const Matrix &b);
        Matrix operator*(const Matrix &b);
        Matrix transpost();
    private:
        Node *headnode;
};

istream &operator>>(istream &is, Matrix &m){
    triple in;
    is >> in.row >> in.col >> in.value; //get matrix information
    int t = max(in.row, in.col);    //check size
    m.headnode = new Node(true, 0);
    if(t==0){   //if no row and col
        m.headnode->right = m.headnode; //point to self
        return is;
    }
    Node **head = new Node *[t];    //create 1d node array
    for (int i = 0; i < t; i++)
        head[i] = new Node(true, 0);    //create header node
    int curRow = 0;
    Node *last = head[0];   //create 'last' to note last node
    for (int i = 0; i < in.value;i++){  //create element node
        triple t;
        is >> t.row >> t.col >> t.value;    //get element information
        if(t.row>curRow){
            last->right = head[curRow];
            curRow = t.row;
            last = head[curRow];
        }
        last = last->right = new Node(false, &t);
        head[t.col]->next = head[t.col]->next->down = last;
    }
    last->right = head[curRow];
    for (int i = 0; i < in.col;i++)
        head[i]->next->down = head[i];
    for (int i = 0; i < t - 1;t++)
        head[i]->next = m.headnode;
    m.headnode->right = head[0];
    delete[] head;
    return is;
};

ostream &operator<<(ostream &os, const Matrix &m){
    Node *curRow = m.headnode->next;
    Node *curNode;
    while(curRow!=m.headnode){
        curNode = curRow->right;
        while(curNode!=curRow){
            os << curNode->Triple.row << ' ' 
            << curNode->Triple.col << ' ' 
            << curNode->Triple.value << endl;
            curNode = curNode->right;
        }
        curRow = curRow->next;
    }
    return os;
};

Matrix::Matrix(const Matrix &a){
    this->headnode = a.headnode;
};

const Matrix &Matrix::operator=(const Matrix &a){
    return *this;
};

Matrix::~Matrix(){
    if(!headnode)
        return;
    Node *x = headnode->right;
    static Node *av;
    headnode->right = av;
    av = headnode;
    while(x!=headnode){
        Node *y = x->right;
        x->right = av;
        av = y;
        x = x->next;
    }
    headnode = 0;
};

Matrix Matrix::operator+(const Matrix &b){
    Node *beP = this->headnode->next;
    Node *toP = b.headnode->next;
    Node *ptr,*temp;
    while(toP!=b.headnode){
        if(beP->right->Triple.row==toP->right->Triple.row
        &&beP->right->Triple.col==toP->right->Triple.col){
            //row and col are same
            //value
            beP->right->Triple.value += toP->right->Triple.value;
        }else if(beP->right->Triple.row<toP->right->Triple.row){
            //row of toP is bigger than row of beP
            beP = beP->next;
            continue;
        }else if(beP->right->Triple.col>toP->right->Triple.col){
            //toP's col is smaller than beP's col
            //add node
            for (int i = 0; i < toP->right->Triple.col;i++)
                ptr = this->headnode->next;
                //move ptr to correct col
            triple ans = toP -> right->Triple;
            //get toP's triple
            temp = beP;
            temp->right = beP->right;
            beP->right = new Node(false, &ans);
            //create new node
            beP->right->right = temp->right;
            if(ptr->next->down->Triple.row!=beP->right->Triple.row)
            ptr->next->down = beP->right;
        }else if(beP->right->Triple.col<toP->right->Triple.col){

        }
        toP = toP->next;
    }
    return *this;
};

Matrix Matrix::operator-(const Matrix &b){
    return *this;
};

Matrix Matrix::operator*(const Matrix &b){
    return *this;
};

Matrix Matrix::transpost(){
    return *this;
};

int main(){
    
}