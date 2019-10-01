#include <iostream>
#include <string>


using namespace std;

string InfixToPostfix(string);
string InfixToPrefix(string);

template <class T>
class Stack{
    private:
        T *stack;
        int top;
        int capacity;
    public:
        Stack(int stackCapacity = 100);
        bool empty() const;
        T& Top() const;
        void push(const T& item);
        void pop();
};
template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity){
    //if(capacity<1)
    //    throw "Stack capacity must be >0";
    stack = new T[capacity];
    top = -1;
}
template <class T>
bool Stack<T>::empty() const { return top == -1; }
template <class T>
T& Stack<T>::Top() const{
    //if(empty())
    //    throw "Stack is empty";
    return stack[top];
}
template <class T>
void Stack<T>::push(const T& item){
    if(top==capacity-1){
        capacity *= 2;
        T *newStack = new T[capacity];
        for (int i = 0; i < capacity / 2; i++){
            newStack[i] = stack[i];
        }
        delete[] stack;
        stack = newStack;
    }
    stack[++top] = item;
}
template <class T>
void Stack<T>::pop(){
    //if(empty())
    //    throw "Stack is empty. Cannot delete";
    top--;
}

int main(){
    string input;
    while(cin>>input){
        cout << "Postfix: " << InfixToPostfix(input) << endl;
        cout << "Prefix: " << InfixToPrefix(input) << endl << endl;    
    };
    return 0;
}

string InfixToPostfix(string a){
    string ans;
    Stack<char> seq;
    for (int i=0; i < a.length();i++){
        if(seq.empty()&&(a[i]=='('||a[i]==')'||a[i]=='*'||a[i]=='/'||a[i]=='+'||a[i]=='-')){
            seq.push(a[i]);
            continue;
        };
        switch(a[i]){
            case '(':
                seq.push(a[i]);
                break;
            case ')':
                if(seq.Top()=='('){
                    seq.pop();
                    break;
                };
                while(seq.Top() != '('){
                    ans += seq.Top();
                    seq.pop();
                    if(seq.Top()=='('){
                        seq.pop();
                        break;
                    };
                };
                break;
            case '*':
            case '/':
                while(seq.Top()=='*'||seq.Top()=='/'){
                    ans += seq.Top();
                    seq.pop();
                    if(seq.empty()==1){
                        break;
                    };
                };
                seq.push(a[i]);
                break;
            case '+':
            case '-':
                while(seq.Top()=='+'||seq.Top()=='-'||seq.Top()=='*'||seq.Top()=='/'){
                    ans += seq.Top();
                    seq.pop();
                    if(seq.empty()==1){
                        break;
                    };
                };
                seq.push(a[i]);
                break;
            default:
                ans += a[i];
                break;
        };
    };
    while(seq.empty()!=1){
        ans += seq.Top();
        seq.pop();
    };
    return ans;
}

string InfixToPrefix(string b){
    Stack<char> seq1;   //operator
    Stack<string> seq2;   //operand
    string cache1,cache2,ans;
    for (int j=0; j < b.length();j++){
        switch(b[j]){
            case '(':
                seq1.push(b[j]);
                break;
            case ')':
                while(!seq1.empty()&&seq1.Top() != '('){
                    cache1 = seq2.Top();
                    seq2.pop();
                    cache2 = seq2.Top();
                    seq2.pop();
                    seq2.push(seq1.Top() + cache2 + cache1);
                    seq1.pop();
                };
                seq1.pop();
                break;
            case '*'://2
            case '/':
                while(!seq1.empty()&&(seq1.Top()=='*'||seq1.Top()=='/')){
                    cache1 = seq2.Top();
                    seq2.pop();
                    cache2 = seq2.Top();
                    seq2.pop();
                    seq2.push(seq1.Top() + cache2 + cache1);
                    seq1.pop();
                };
                seq1.push(b[j]);
                break;
            case '+'://1
            case '-':
                while(!seq1.empty()&&(seq1.Top()=='*'||seq1.Top()=='/'||seq1.Top()=='+'||seq1.Top()=='-')){
                    cache1 = seq2.Top();
                    seq2.pop();
                    cache2 = seq2.Top();
                    seq2.pop();
                    seq2.push(seq1.Top() + cache2 + cache1);
                    seq1.pop();
                };
                seq1.push(b[j]);
                break;
            default:
                seq2.push(string(1,b[j]));
                break;
        };
    };
    while(!seq1.empty()){
        cache1 = seq2.Top();
        seq2.pop();
        cache2 = seq2.Top();
        seq2.pop();
        seq2.push(seq1.Top() + cache2 + cache1);
        seq1.pop();
    };
    return seq2.Top();    
}