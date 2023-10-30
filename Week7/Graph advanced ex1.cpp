#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void topoSort(vector<vector<int>> &adj, vector<int> &in_degree, vector<int> &res) {
    queue <int> q;
    int n = adj.size();
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int tmp = q.front();
        q.pop();
        res.push_back(tmp);
        for (int v : adj[tmp]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1,0);
    for (int i = 0; i < m; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }

    vector<int> res;
    topoSort(adj,in_degree,res);
    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    return 0;
}
