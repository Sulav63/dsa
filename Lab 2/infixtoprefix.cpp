/*WAP to demonstrate infix to prefix expression conversion*/
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class InfixToPrefixConverter {
private:
    stack<char> st;

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '$');
    }

    bool isOperand(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    int precedence(char c) {
        if (c == '^' || c == '$')
            return 3;
        else if (c == '*' || c == '/')
            return 2;
        else if (c == '+' || c == '-')
            return 1;
        else
            return -1; // Lower precedence
    }

public:
    string infixToPrefix(string infix) {
        string prefix;
        reverse(infix.begin(), infix.end());

        for (int i = 0; i < infix.size(); ++i) {
            char& c = infix[i];
            if (c == '(')
                c = ')';
            else if (c == ')')
                c = '(';
        }

        cout << "\nScan Char\t|\tPost Stack\t|\tOpstack\n";
        cout << "------------------------------------------------------\n";

        for (int i = 0; i < infix.size(); ++i) {
            char& c = infix[i];
            if (isOperand(c)) {
                prefix += c;
            } else if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (st.size() > 0 && st.top() != '(') {
                    prefix += st.top();
                    st.pop();
                }
                if (st.size() > 0 && st.top() == '(')
                    st.pop(); // Discard the '('
            } else if (isOperator(c)) {
                while (st.size() > 0 && precedence(st.top()) >= precedence(c)) {
                    prefix += st.top();
                    st.pop();
                }
                st.push(c);
            }

            // Print step details
            cout << c << "\t\t|\t";
            stack<char> temp = st;
            bool stackEmpty = temp.size() == 0;
            while (!temp.empty()) {
                cout << temp.top();
                temp.pop();
                if (!temp.empty()) stackEmpty = false;
            }
            if (stackEmpty) cout << " ";
            cout << "\t\t|\t" << prefix << endl;

        }

        while (st.size() > 0) {
            prefix += st.top();
            st.pop();
        }

        reverse(prefix.begin(), prefix.end());
        return prefix;
    }
};

int main() {
    InfixToPrefixConverter conv;
    string infixExpr;

    cout << "Enter an infix expression: ";
    getline(cin, infixExpr);

    string prefixExpr = conv.infixToPrefix(infixExpr);
    cout << "\nPrefix expression: " << prefixExpr << endl;

    return 0;
}

