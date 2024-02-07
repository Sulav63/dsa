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

    void mainProcess()
    {
        char scanCh;

        for (int i = 0; i < MAX_LENGTH && postfixExpression[i] != '\0'; i++) // CONVERTING VARIABLES OF POSTFIX EXPRESSION TO INTEGER WHILE TAKING THEIR
        // VALUES SIMULTANEOUSLY
        {
            if (isAlphabet(postfixExpression[i]) == 1) // RETURNS 1 OF EXPRESSION IS AN ALPHABET
            {
                cout << "Enter value of " << postfixExpression[i] << " : ";
                cin >> postInt[numOfAlphabets]; // STORING THE VALUES OF ALPHABETS IN ARRAY WITH POSTFIX EXPRESSION THAT
                // IS CONVERTED TO INTEGER
                alphabetIndexArray[numOfAlphabets] = i; // STORES INDEXES IN AN ARRAY WHICH WILL BE USEFUL LATER
                numOfAlphabets++;                       // INCREMENT IS DONE LATER AS INITIAL VALUE OF numOfAlphabets is 0
            }
        }

        cout << "Scan \t\t OP1 \t\t OP2 \t\t Operator \t\t Stack" << endl;
        for (int i = 0; i < MAX_LENGTH && postfixExpression[i] != '\0'; i++)
        {
            scanCh = postfixExpression[i];
            if (i == alphabetIndexArray[alphaIndex])
            {

                cout << postInt[alphaIndex] << " \t\t "; // alphaIndex is the index of number of alphabets found from 0 so it
                // increments every time an alphabet is found and can match it's contents with i in previous if case
                // and postInt will be displayed with same index
                cout << "XXX \t\t XXX \t\t XXX \t\t";
                pushToStack(postInt[alphaIndex]);
                traverse_stack();
                cout << endl;
                alphaIndex++;
            }
            else
            {
                cout << scanCh << " \t\t ";
                op1 = stack[stackTop - 1]; // PULLING VALUES FROM STACK
                cout << op1 << "  \t\t  ";
                op2 = stack[stackTop]; // PULLING VALUES FROM STACK
                cout << op2 << "  \t\t  ";
                op = scanCh; // PUTTING THE OPERATOR IN VARIABLE TO PUT IN FUNCTION AS ARGUMENT
                cout << op << "  \t\t  ";
                popFromStack(); // HAVE TO REMOVE OP1 AND OP2 FROM STACK THEN ONLY PUT VALUE IN STACK FROM operatorOperation function
                popFromStack();
                pushToStack(operatorOperation(op1, op, op2)); // PUSHES ANSWER FROM THE FUNCTION
                traverse_stack();
                cout << endl;
            }
        }
        cout<<endl;
    }
};


int main() {
    InfixToPostfixConverter conv;
    string infixExpr;
    PostEvaluator p1;
    p1.mainProcess();

    cout << "Enter an infix expression: ";
    getline(cin, infixExpr);

    string postfixExpr = conv.toPostfix(infixExpr);
    cout << "\nPostfix expression: " << postfixExpr << endl;

    conv.inputVarVals(infixExpr);

    int result = conv.evalPostfix();
    cout << "Result: " << result << endl;

    return 0;
}

