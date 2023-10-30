#include <bits/stdc++.h>

using namespace std;

int findShortest(int n, int m, int X, int Y,vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n);
    for (pair<int, int>& edge : edges) {
        int u = edge.first - 1;
        int v = edge.second - 1;
        adj[u].push_back(v);
    }

    vector<int> kc(n, INT_MAX);
    queue<int> q;
    q.push(X - 1);
    kc[X - 1] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int child : adj[node]) {
            if (kc[child] == INT_MAX) {
                kc[child] = kc[node] + 1;
                q.push(child);
            }
        }
    }
    int res = 0;
    if (kc[Y-1] == INT_MAX) res = -1;
    else res = kc[Y-1];

    return res;
}

int main() {
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int shortest = findShortest(n, m, X, Y, edges);
    cout << shortest << endl;

    return 0;
}

