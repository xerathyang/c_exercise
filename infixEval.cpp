#include <iostream>
#include <string>
#include <vector>

using namespace std;

int prio(char op) {
    switch(op) {
    case'*':
    case'/':
        return 2;
    case'+':
    case'-':
        return 1;
    default:
        return 0;
    }
}

string topostfix(string infix) {
    vector<char> stack;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        switch (infix[i]) {
        case' ':
            break;
        case'+':
        case'-':
        case'*':
        case'/':
            while (stack.size() > 0 && prio(stack.back()) >= prio(infix[i])) {
                postfix += stack.back();
                postfix += " ";
                stack.pop_back();
            }
        case'(':
            stack.push_back(infix[i]);
            break;
        case')':
            while (stack.back() != '(') {
                postfix += stack.back();
                postfix += ' ';
                stack.pop_back();
            }
            stack.pop_back();
            break;
        default:
            postfix += infix[i];
            while (isdigit(infix[i + 1])) {
                i++;
                postfix += infix[i];
            }
            postfix += " ";
            break;
        }
    }
    while (stack.size() > 0) {
        postfix += stack.back();
        stack.pop_back();
        if (stack.size() > 0)
            postfix += " ";
    }
    return postfix;
}

double posttodouble(string postfix) {
    vector<double> stack;
    string num = "";
    double n1 = 0, n2 = 0;
    for (int i = 0; i < postfix.length(); i++) {
        switch (postfix[i]) {
        case ' ':
            if (num != "") {
                stack.push_back(stod(num));
                num = "";
            }
            break;
        case'+':
        case'-':
        case'*':
        case'/':
            n1 = stack.back();
            stack.pop_back();
            n2 = stack.back();
            stack.pop_back();
            if (postfix[i] == '+')
                stack.push_back(n2 + n1);
            else if (postfix[i] == '-')
                stack.push_back(n2 - n1);
            else if (postfix[i] == '*')
                stack.push_back(n2 * n1);
            else if (postfix[i] == '/')
                stack.push_back(n2 / n1);
            break;
        default:
            num += postfix[i];
            break;
        }
    }
    return stack.back();
}

int main()
{
    string input;
    while (cin >> input) {
        string tmp = topostfix(input);
        cout << posttodouble(tmp) << endl;
    }
}