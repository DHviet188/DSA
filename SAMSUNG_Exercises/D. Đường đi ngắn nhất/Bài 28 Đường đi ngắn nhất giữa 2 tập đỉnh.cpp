#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

const int INF = 1e9;
vector<vector<pii>> adj;
int dijkstra(int V, const vector<int>& S, const vector<int>& T) {
    vector<int> dist(V, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (int s : S) {
        dist[s] = 0;
        pq.push({0, s});
    }

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (find(T.begin(), T.end(), u) != T.end()) {
            return d;
        }

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return -1;
}

int main() {
    int V = 5;
    adj.resize(V);

    adj[0].push_back({1, 4});
    adj[0].push_back({2, 1});
    adj[1].push_back({3, 1});
    adj[2].push_back({1, 2});
    adj[2].push_back({3, 5});
    adj[3].push_back({4, 3});

    vector<int> S = {0};
    vector<int> T = {4};

    int shortestPath = dijkstra(V, S, T);
    if (shortestPath != -1) {
        cout << "Đường đi ngắn nhất từ S đến T: " << shortestPath << endl;
    } else {
        cout << "Không có đường đi từ S đến T." << endl;
    }

    return 0;
}
