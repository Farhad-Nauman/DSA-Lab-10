#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int id;
    int cost;
    Node* left;
    Node* right;
};
Node* createNode(int id, int cost) {
    Node* temp = new Node;

    temp->id = id;
    temp->cost = cost;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
Node* insert(Node* root, int id, int cost) {
    if (root == NULL)
        return createNode(id, cost);

    if (cost < root->cost)
        root->left = insert(root->left, id, cost);

    else if (cost > root->cost)
        root->right = insert(root->right, id, cost);
    return root;
}
void printPath(vector<Node*>& path, int target) {
    int sum = 0;

    for (int i = path.size() - 1; i >= 0; i--) {
        sum += path[i]->cost;

        if (sum == target) {
            cout << "Path: ";

            for (int j = i; j < path.size(); j++)
                cout << path[j]->id << "("
                     << path[j]->cost << ") ";

            cout << endl;
        }
    }
}
void pathBacktrack(Node* root, vector<Node*>& path,
                   int target) {

    if (root == NULL)
        return;
    path.push_back(root);

    printPath(path, target);

    pathBacktrack(root->left, path, target);
    pathBacktrack(root->right, path, target);

    path.pop_back();
}
void inorder(Node* root, vector<Node*>& nodes) {
    if (root == NULL)
        return;

    inorder(root->left, nodes);

    nodes.push_back(root);

    inorder(root->right, nodes);
}
void printSubset(vector<Node*>& current) {
    cout << "Subset: ";

    for (Node* node : current)
        cout << node->id << "(" << node->cost << ") ";

    cout << endl;
}
void subsetBacktrack(vector<Node*>& nodes, int index,
                     int sum, int target,
                     vector<Node*>& current) {

    if (sum == target) {
        printSubset(current);
        return;
    }

    if (index == nodes.size())
        return;

    if (sum + nodes[index]->cost > target)
        return;

    current.push_back(nodes[index]);

    subsetBacktrack(nodes, index + 1,
                    sum + nodes[index]->cost,
                    target, current);

    current.pop_back();

    subsetBacktrack(nodes, index + 1,
                    sum, target, current);
}
int main() {
    Node* root = NULL;
    int n;
    cout << "Enter number of services: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int id, cost;

        cout << "Enter service ID and monthly cost: ";
        cin >> id >> cost;

        root = insert(root, id, cost);
    }
    int target;
    cout << "Enter target budget: ";
    cin >> target;
    vector<Node*> path;
    cout << "\nPart A: Downward Paths\n";
    pathBacktrack(root, path, target);
    vector<Node*> nodes;
    inorder(root, nodes);
    vector<Node*> current;
    cout << "\nPart B: BST Subsets\n";
    subsetBacktrack(nodes, 0, 0, target, current);
    return 0;
}
