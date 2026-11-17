
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int id;
    int weight;
    Node* next;
};
void insert(Node*& head, int id, int weight) { // insert weigth and id of conatiners
    Node* temp = new Node{id, weight, NULL};

    if (head == NULL) {
        head = temp;
        return;
    }
    Node* curr = head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = temp;
}
int remainingWeight(Node* curr) {        // calculates the remaining weitght of containers according to truck capacity
    int sum = 0;

    while (curr != NULL) {
        sum += curr->weight;
        curr = curr->next;
    }
    return sum;
}
bool backtrack(Node* curr, queue<int> trucks,
               vector<vector<int>>& answer,
               int truckCount) {

    if (curr == NULL) {
        cout << "\nAll containers loaded successfully!\n";

        for (int i = 0; i < truckCount; i++) {
            cout << "Truck " << i + 1 << ": ";

            if (answer[i].empty())
                cout << "Empty";

            for (int id : answer[i])
                cout << id << " ";

            cout << endl;
        }
        return true;
    }
    if (trucks.empty())
        return false;

    int totalCapacity = 0;
    queue<int> temp = trucks;
    while (!temp.empty()) {
        totalCapacity += temp.front();
        temp.pop();
    }
    if (remainingWeight(curr) > totalCapacity)
        return false;

    int capacity = trucks.front();
    trucks.pop();
    vector<int> currentLoad;
    Node* tempNode = curr;
    int usedWeight = 0;

    while (tempNode != NULL &&
           usedWeight + tempNode->weight <= capacity) {

        usedWeight += tempNode->weight;
        currentLoad.push_back(tempNode->id);

        answer.push_back(currentLoad);

        if (backtrack(tempNode->next, trucks, answer, truckCount))
            return true;

        answer.pop_back();

        tempNode = tempNode->next;
    }
    return false;
}
int main() {
    Node* head = NULL;
    int n;
    cout << "Enter number of containers: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int id, weight;

        cout << "Enter container ID and weight: ";
        cin >> id >> weight;

        insert(head, id, weight);
    }

    queue<int> trucks;
    int t;
    cout << "Enter number of trucks: ";   //enter number of trucks in queue
    cin >> t;
    for (int i = 0; i < t; i++) {
        int capacity;

        cout << "Enter capacity of truck " << i + 1 << ": ";
        cin >> capacity;

        trucks.push(capacity);
    }
    vector<vector<int>> answer;

    if (!backtrack(head, trucks, answer, t))
        cout << "Insufficient truck capacity.";
    return 0;
}
