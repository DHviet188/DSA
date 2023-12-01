#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii; // Đỉnh, Khoảng cách

const int INF = 1e9;
vector<vector<pii>> adj; // Danh sách kề

// Giả sử hàm dijkstra đã được cài đặt
vector<int> dijkstra(int s, int V);

vector<int> findBitonicShortestPaths(int s, int V) {
    vector<int> distIncrease = dijkstra(s, V); // Đường đi tăng từ s
    vector<int> distDecrease = dijkstraReverse(s, V); // Đường đi giảm đến s (trên đồ thị đảo ngược)

    vector<int> bitonicDist(V, INF);
    for (int v = 0; v < V; ++v) {
        for (int x = 0; x < V; ++x) { // Xét tất cả các đỉnh trung gian
            if (distIncrease[x] != INF && distDecrease[v] != INF) {
                bitonicDist[v] = min(bitonicDist[v], distIncrease[x] + distDecrease[v]);
            }
        }
    }

    return bitonicDist;
}

int main() {
    int V = 5; // Giả sử đồ thị có 5 đỉnh
    adj.resize(V);

    // Thêm cạnh vào đồ thị
    adj[0].push_back({1, 3});
    adj[1].push_back({0, 3});
    adj[1].push_back({2, 2});
    adj[2].push_back({1, 2});
    adj[2].push_back({3, 4});
    adj[3].push_back({2, 4});
    adj[3].push_back({4, 1});
    adj[4].push_back({3, 1});

    vector<int> bitonicDist = findBitonicShortestPaths(0, V);

    cout << "Đường đi bitonic ngắn nhất từ đỉnh 0 đến mỗi đỉnh khác:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Đến đỉnh " << i << ": " << (bitonicDist[i] == INF ? "Không thể đạt được" : to_string(bitonicDist[i])) << endl;
    }

    return 0;
}
