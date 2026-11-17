#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

bool applyOperation(int value, string op, int bound, int& result) { // atomic operations into stack
    char symbol = op[0];
    int num = stoi(op.substr(1));

    if (symbol == '+')
        result = value + num;

    else if (symbol == '-')
        result = value - num;

    else if (symbol == '*')
        result = value * num;

    else if (symbol == '/') {
        if (num == 0 || value % num != 0)
            return false;

        result = value / num;
    }
    else
        return false;

    if (result < 0 || result > bound)
        return false;

    return true;
}
void backtrack(int current, int target, int budget,     // backtracks the operation from stack 
               int bound, vector<string>& operations,
               stack<string>& st) {

    if (current == target) {
        stack<string> temp = st;
        vector<string> sequence;

        while (!temp.empty()) {
            sequence.push_back(temp.top());
            temp.pop();
        }
        cout << "Sequence: ";

        for (int i = sequence.size() - 1; i >= 0; i--)
            cout << sequence[i] << " ";

        cout << endl;
        return;
    }
    if (budget == 0)
        return;

    for (string op : operations) {
        int nextValue;

        if (applyOperation(current, op, bound, nextValue)) {

            st.push(op);
            backtrack(nextValue, target, budget - 1,
                      bound, operations, st);
            st.pop();
        }
    }
}
int main() {                              
    int initial, target, budget, bound;
    cout << "Enter initial state: ";
    cin >> initial;

    cout << "Enter target state: ";
    cin >> target;

    cout << "Enter maximum operation budget: ";
    cin >> budget;

    cout << "Enter overflow bound: ";
    cin >> bound;

    int n;
    cout << "Enter number of allowed operations: "; // enter the number of allowed atomix operations
    cin >> n;
    vector<string> operations;
    for (int i = 0; i < n; i++) {
        string op;

        cout << "Enter operation: ";
        cin >> op;

        operations.push_back(op);
    }
    stack<string> st;

    cout << "\nValid sequences:\n";

    backtrack(initial, target, budget, bound, operations, st);
    return 0;
}
