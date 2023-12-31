#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V; // Số lượng đỉnh
    vector<vector<int>> adj; // Danh sách kề

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack);
public:
    Graph(int V);
    void addEdge(int v, int w);
    bool hasHamiltonianPath();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;
    for (int i : adj[v])
        if (!visited[i])
            topologicalSortUtil(i, visited, Stack);
    Stack.push(v);
}

bool Graph::hasHamiltonianPath() {
    stack<int> Stack;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, Stack);

    int last = Stack.top();
    Stack.pop();
    while (!Stack.empty()) {
        int current = Stack.top();
        Stack.pop();
        bool edgeExists = false;
        for (int adjVertex : adj[last])
            if (adjVertex == current) {
                edgeExists = true;
                break;
            }
        if (!edgeExists)
            return false;
        last = current;
    }
    return true;
}

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    if (g.hasHamiltonianPath())
        cout << "Có đường đi Hamiltonian" << endl;
    else
        cout << "Không có đường đi Hamiltonian" << endl;

    return 0;
}
