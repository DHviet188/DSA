#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int INF = 1e9;

struct Edge {
    int v, weight;
};

vector<int> dijkstraOptimized(const vector<vector<Edge>>& adj, int s, int V, int C) {
    vector<int> dist(V, INF);
    vector<list<int>> bucket(C);
    dist[s] = 0;
    bucket[0].push_back(s);

    for (int i = 0; i < C; ++i) {
        while (!bucket[i].empty()) {
            int u = bucket[i].front();
            bucket[i].pop_front();

            for (const auto& edge : adj[u]) {
                int v = edge.v;
                int w = edge.weight;
                int newDist = dist[u] + w;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    bucket[newDist % C].push_back(v);
                }
            }
        }
    }

    return dist;
}

int main() {
    int V = 4;
    int C = 10;
    vector<vector<Edge>> adj(V);

    adj[0].push_back({1, 4});
    adj[1].push_back({2, 1});
    adj[2].push_back({3, 3});
    adj[3].push_back({1, 2});

    int source = 0; // Đỉnh nguồn
    vector<int> shortestDistances = dijkstraOptimized(adj, source, V, C);

    cout << "Khoảng cách từ đỉnh " << source << " đến các đỉnh khác:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Đến đỉnh " << i << ": " << (shortestDistances[i] == INF ? "Không thể đạt được" : to_string(shortestDistances[i])) << endl;
    }

    return 0;
}
