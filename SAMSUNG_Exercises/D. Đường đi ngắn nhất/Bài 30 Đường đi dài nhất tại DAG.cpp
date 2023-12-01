#include <iostream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (auto i : adj[v]) {
            if (!visited[i.first])
                topologicalSortUtil(i.first, visited, Stack);
        }
        Stack.push(v);
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
    }

    void longestPath(int s) {
        stack<int> Stack;
        vector<int> dist(V, INT_MIN);
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                topologicalSortUtil(i, visited, Stack);

        dist[s] = 0;

        while (!Stack.empty()) {
            int u = Stack.top();
            Stack.pop();

            if (dist[u] != INT_MIN) {
                for (auto i : adj[u])
                    if (dist[i.first] < dist[u] + i.second)
                        dist[i.first] = dist[u] + i.second;
            }
        }

        for (int i = 0; i < V; i++)
            (dist[i] == INT_MIN) ? cout << "INF " : cout << dist[i] << " ";
        cout << endl;
    }
};

int main() {
    // Tạo đồ thị
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int s = 1;
    cout << "Đường đi dài nhất từ đỉnh " << s << ":\n";
    g.longestPath(s);

    return 0;
}
