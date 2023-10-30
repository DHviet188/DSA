#include <bits/stdc++.h>

using namespace std;

void dfs(int node,vector<vector<int>> & graph,vector<bool>& visited) {
    visited[node] = true;
    for (int child : graph[node]) {
        if (!visited[child]) {
            dfs(child, graph, visited);
        }
    }
}

int count(int n,vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n);
    for (pair<int, int>& edge : edges) {
        int u = edge.first - 1;
        int v = edge.second - 1;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n, false);
    int cpn = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited);
            cpn++;
        }
    }

    return cpn;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int res = count(n, edges);
    cout << res << endl;

    return 0;
}

