#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef pair<int, double> pii;

const int INF = 1e9;
vector<vector<pii>> adj;

double euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void dijkstra(int start, const vector<pair<int, int>>& coordinates) {
    int V = coordinates.size();
    vector<double> dist(V, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().first;
        double d = pq.top().second;
        pq.pop();

        for (auto& edge : adj[u]) {
            int v = edge.first;
            double w = euclideanDistance(coordinates[u].first, coordinates[u].second,
                                         coordinates[v].first, coordinates[v].second);
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({v, dist[v]});
            }
        }
    }
    cout << "Khoảng cách từ đỉnh " << start << " đến các đỉnh khác:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Đến đỉnh " << i << ": " << dist[i] << endl;
    }
}

int main() {
    int V = 5;
    adj.resize(V);
    vector<pair<int, int>> coordinates = {{0, 0}, {1, 1}, {1, 2}, {2, 2}, {3, 3}};

    dijkstra(0, coordinates);

    return 0;
}

