#include <iostream>
#include <stack>
#include <cctype>
#include <map>
#include <cmath>

using namespace std;

class InfixToPostfixConverter {
private:
    stack<char> st;
    map<char, int> varVals;
    string postfixExpr;

    bool isOp(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '$');
    }

    int getPrec(char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        } else if (op == '$') {
            return 3;
        }
        return 0;
    }

    string getStackContent() {
        string content;
        stack<char> temp = st;
        while (temp.size() > 0) {
            content = temp.top() + content;
            temp.pop();
        }
        return content;
    }

public:
    string toPostfix(const string &infix) {
        string postfix = "";
        cout << "\nScan Character\t\t|\tPost Stack\t|\tOp Stack\n";
        cout << "------------------------------------------------------------------------------\n";
        for (int i = 0; i < infix.size(); ++i) {
            char c = infix[i];
            if (c == '^') {
                postfix += '$';  // Display '^' as '$'
            } else if (isalnum(c)) {
                postfix += c;
                cout << c << "\t\t\t|\t" << getStackContent() << "\t\t|\t" << postfix << "\t\t\t" << endl;
            } else if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (st.size() > 0 && st.top() != '(') {
                    postfix += st.top();
                    st.pop();
                }
                st.pop(); // Discard the '('
                cout << ")\t\t\t|\t" << getStackContent() << "\t\t|\t" << postfix << "\t\t\t" << endl;
            } else if (isOp(c)) {
                while (st.size() > 0 && getPrec(st.top()) >= getPrec(c)) {
                    postfix += st.top();
                    st.pop();
                }
                st.push(c);
                cout << c << "\t\t\t|\t" << getStackContent() << "\t\t|\t" << postfix << "\t\t\t" << endl;
            }
        }

        while (st.size() > 0) {
            postfix += st.top();
            st.pop();
        }

        postfixExpr = postfix;
        return postfixExpr;
    }

    void inputVarVals(const string &infix) {
        for (int i = 0; i < infix.size(); ++i) {
            char c = infix[i];
            if (isalpha(c) && varVals.find(c) == varVals.end()) {
                int val;
                cout << "Enter value for variable '" << c << "': ";
                cin >> val;
                varVals[c] = val;
            }
        }
        cout << "\nVariable Values\n";
        cout << "----------------\n";
        for (map<char, int>::iterator it = varVals.begin(); it != varVals.end(); ++it) {
            cout << it->first << " = " << it->second << endl;
        }

        // Display the expression with numbers
        cout << "\nExpression with Numbers:\n";
        for (int i = 0; i < infix.size(); ++i) {
            char c = infix[i];
            if (isalpha(c)) {
                cout << varVals[c];
            } else {
                cout << c;
            }
        }
        cout << endl;
    }

    int evalPostfix() {
        stack<int> operands;
        cout << "\nInput Symbol\t|\tOperator\t|\tOperand 1\t|\tOperand 2\t|\tStack\n";
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < postfixExpr.size(); ++i) {
            char c = postfixExpr[i];
            if (isalnum(c)) {
                operands.push(varVals[c]);
                cout << c << "\t\t|\t\t\t|\t\t\t|\t\t\t|\t" << getStackContent() << endl;
            } else if (isOp(c)) {
                int op2 = operands.top();
                operands.pop();
                int op1 = operands.top();
                operands.pop();
                cout << c << "\t\t|\t" << c << "\t\t|\t" << op1 << "\t\t|\t" << op2 << "\t\t|\t" << getStackContent() << endl;

                switch (c) {
                case '+':
                    operands.push(op1 + op2);
                    break;
                case '-':
                    operands.push(op1 - op2);
                    break;
                case '*':
                    operands.push(op1 * op2);
                    break;
                case '/':
                    operands.push(op1 / op2);
                    break;
                case '$':
                    operands.push(pow(op1, op2));
                    break;
                }
            }
        }

        return operands.top();
    }

    void mainProcess()
    {
        char scanCh;

        for (int i = 0; i < MAX_LENGTH && postfixExpression[i] != '\0'; i++)
        {
            scanCh = postfixExpression[i];
            if (i == alphabetIndexArray[alphaIndex])
            {
                cout << postInt[alphaIndex] << " \t\t ";
                cout << "XXX \t\t XXX \t\t XXX \t\t";
                pushToStack(postInt[alphaIndex]);
                traverse_stack();
                cout << endl;
                alphaIndex++;
            }
            else
            {
                cout << scanCh << " \t\t ";
                op1 = stack[stackTop - 1];
                cout << op1 << "  \t\t  ";
                op2 = stack[stackTop];
                cout << op2 << "  \t\t  ";
                op = scanCh;
                cout << op << "  \t\t  ";
                popFromStack();
                popFromStack();
                pushToStack(operatorOperation(op1, op, op2));
                traverse_stack();
                cout << endl;
            }
        }

        // Display the final stack content
        cout << "Final Stack:\t";
        traverse_stack();
        cout << endl;
    }
};

int main()
{
    InfixToPostfixConverter conv;
    string infixExpr;

    cout << "Enter an infix expression: ";
    getline(cin, infixExpr);

    string postfixExpr = conv.toPostfix(infixExpr);
    cout << "\nPostfix expression: " << postfixExpr << endl;

    conv.inputVarVals(infixExpr);

    int result = conv.evalPostfix();
    cout << "Result: " << result << endl;

    return 0;
}

