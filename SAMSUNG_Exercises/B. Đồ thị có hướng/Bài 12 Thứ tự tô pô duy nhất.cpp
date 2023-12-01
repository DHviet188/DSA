#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack);
public:
    Graph(int V);
    void addEdge(int v, int w);
    bool hasUniqueTopologicalSort();
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

bool Graph::hasUniqueTopologicalSort() {
    stack<int> Stack;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, Stack);

    int prev = Stack.top();
    Stack.pop();
    while (!Stack.empty()) {
        int curr = Stack.top();
        Stack.pop();
        auto it = find(adj[prev].begin(), adj[prev].end(), curr);
        if (it == adj[prev].end())
            return false;
        prev = curr;
    }
    return true;
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    if (g.hasUniqueTopologicalSort())
        cout << "Đồ thị có thứ tự tô pô duy nhất." << endl;
    else
        cout << "Đồ thị không có thứ tự tô pô duy nhất." << endl;

    return 0;
}
