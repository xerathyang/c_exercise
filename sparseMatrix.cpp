#include <iostream>

using namespace std;

struct triple{
    int row, col, value;
};

class Matrix;
class Node{
    friend class Matrix;
    friend istream &operator>>(istream &is, Matrix &m);
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

};

Matrix::Matrix(const Matrix &a){
    this->headnode = a.headnode;
};

const Matrix &Matrix::operator=(const Matrix &a){

};

Matrix::~Matrix(){
    if(!headnode)
        return;
    Node *x = headnode->right;
    Node *av;
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

};

Matrix Matrix::operator-(const Matrix &b){

};

Matrix Matrix::operator*(const Matrix &b){

};

Matrix Matrix::transpost(){

};

int main(){
    
}