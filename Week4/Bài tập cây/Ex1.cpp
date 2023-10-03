#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node {
    int data;
    vector<Node*> children;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    return newNode;
}

Node* buildTree(int N, int M, vector<int>& parent) {
    vector<Node*> nodes(N);
    for (int i = 0; i < N; ++i) {
        nodes[i] = createNode(i + 1);
    }

    Node* root = nullptr;
    for (int i = 0; i < N; ++i) {
        int u = parent[i];
        if (u == 0) {
            root = nodes[i];
        } else {
            nodes[u - 1]->children.push_back(nodes[i]);
        }
    }
    return root;
}

int height(Node* root) {
    if (!root) return 0;
    int maxHeight = 0;
    for (Node* child : root->children) {
        int childHeight = height(child);
        maxHeight = max(maxHeight, childHeight);
    }
    return 1 + maxHeight;
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    for (Node* child : root->children) {
        preorder(child);
    }
}

void postorder(Node* root) {
    if (!root) return;
    for (Node* child : root->children) {
        postorder(child);
    }
    cout << root->data << " ";
}

void inorder(Node* root) {
    if (!root) return;
    if (root->children.size() != 2) {
        cout << "NOT BINARY TREE" << endl;
        return;
    }
    inorder(root->children[0]);
    cout << root->data << " ";
    inorder(root->children[1]);
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> parent(N);
    for (int i = 0; i < N; ++i) {
        cin >> parent[i];
    }

    Node* root = buildTree(N, M, parent);

    int treeHeight = height(root);
    cout << treeHeight << endl;

    preorder(root);
    cout << endl;

    postorder(root);
    cout << endl;

    inorder(root);
    cout << endl;

    return 0;
}

