#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node *next;
};

class Stack {
    Node *top;

public:
    Stack() {
        top = NULL;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(char value) {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        Node *temp = top;
        char value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }

    char peek() {
        return top->data;
    }
};

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool shouldPop(char topOp, char currentOp, bool prefixMode) {
    int pt = precedence(topOp);
    int pc = precedence(currentOp);
    if (currentOp == '^') {
        if (prefixMode) return pt >= pc;
        return pt > pc;
    }
    if (prefixMode) return pt > pc;
    return pt >= pc;
}

string infixToPostfix(string infix, bool prefixMode) {
    Stack s;
    string result = "";

    for (int i = 0; i < (int)infix.length(); i++) {
        char ch = infix[i];

        if (ch == ' ') {
            continue;
        }

        if (isalnum(ch)) {
            result += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                result += s.pop();
            }
            if (!s.isEmpty()) {
                s.pop();
            }
        } else {
            while (!s.isEmpty() && s.peek() != '(' && shouldPop(s.peek(), ch, prefixMode)) {
                result += s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        result += s.pop();
    }

    return result;
}

string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < (int)infix.length(); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    string result = infixToPostfix(infix, true);
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string infix;
    cout << "Enter infix expression (single letter/digit operands): ";
    getline(cin, infix);

    cout << "Postfix: " << infixToPostfix(infix, false) << "\n";
    cout << "Prefix: " << infixToPrefix(infix) << "\n";

    return 0;
}
