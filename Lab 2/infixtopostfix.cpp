/*WAP to demonstrate infix to postfix expression conversion*/
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class InfixToPostfixConverter {
private:
    stack<char> st;

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '$ ');
    }

    bool isAlphanumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }

    int getPrecedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        } else if (op == '$') {
            return 3;
        }
        return 0;
    }

public:
    string postfixExpr;

    string toPostfix(const string &infix) {
        string postfix = "";
        cout << "Scan Char\t|\tPost Stack\t|\tOpstack\n";
        cout << "------------------------------------------------\n";
        for (int i = 0; i < infix.size(); ++i) {
            char c = infix[i];
            if (isAlphanumeric(c)) {
                postfix += c;
            } else if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (st.size() > 0 && st.top() != '(') {
                    postfix += st.top();
                    st.pop();
                }
                if (st.size() > 0 && st.top() == '(') {
                    st.pop(); // Discard the '('
                }
            } else if (isOperator(c)) {
                while (st.size() > 0 && getPrecedence(st.top()) >= getPrecedence(c)) {
                    postfix += st.top();
                    st.pop();
                }
                st.push(c);
            }
            // Print step details
            cout << c << "\t\t|\t";
            stack<char> temp = st;
            while (temp.size() > 0) {
                cout << temp.top();
                temp.pop();
            }
            cout << "\t\t|\t" << postfix << endl;
        }

        while (st.size() > 0) {
            postfix += st.top();
            st.pop();
        }

        postfixExpr = postfix;
        return postfix;
    }
};

int main() {
    InfixToPostfixConverter conv;
    string infixExpr;

    cout << "Enter an infix expression: ";
    getline(cin, infixExpr);

    string postfixExpr = conv.toPostfix(infixExpr);
    cout << "Postfix expression: " << postfixExpr << endl;

    return 0;
}

