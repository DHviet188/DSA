// Sử dụng thuật toán Kruval để lưu cạnh nhỏ nhất tới mỗi đỉnh
// Sau đó connect các cạnh lại với nhau để tìm cây khung nhỏ nhất
// Thay vì lưu toàn bộ cạnh, ta chỉ lưu cạnh nhỏ nhất tới mỗi đỉnh
// Vì bộ nhớ bị giới hạn
#include <iostream>
#include <vector>
#include <queue>
#include <functional>  // std::greater
#include <limits>

using namespace std;

// Định nghĩa cấu trúc cạnh
struct Edge {
    int dest, weight;
};

// Định nghĩa cấu trúc đỉnh của đồ thị
struct Node {
    vector<Edge> edges;
    bool inMST;
};

// Hàm tính cây bao trùm nhỏ nhất sử dụng thuật toán Prim
void primMST(vector<Node>& graph, int start) {
    int V = graph.size();

    // Priority queue để chọn cạnh có trọng số nhỏ nhất
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Khởi tạo mảng dist để lưu trọng số nhỏ nhất đến mỗi đỉnh
    vector<int> dist(V, numeric_limits<int>::max());

    // Bắt đầu từ đỉnh start
    pq.push(make_pair(0, start));
    dist[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (graph[u].inMST)
            continue;

        graph[u].inMST = true;

        // Duyệt qua tất cả các cạnh của đỉnh u
        for (const Edge& edge : graph[u].edges) {
            int v = edge.dest;
            int weight = edge.weight;

            // Nếu đỉnh v không thuộc cây bao trùm và trọng số nhỏ hơn trọng số hiện tại
            if (!graph[v].inMST && weight < dist[v]) {
                dist[v] = weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // In kết quả
    int totalWeight = 0;
    cout << "Edges in MST:" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] != numeric_limits<int>::max()) {
            totalWeight += dist[i];
            cout << start << " - " << i << " Weight " << dist[i] << endl;
        }
    }

    cout << "Total weight of MST: " << totalWeight << endl;
}

int main() {
    int V = 6;
    vector<Node> graph(V);

    // Thêm cạnh vào đồ thị
    graph[0].edges.push_back({1, 2});
    graph[0].edges.push_back({2, 4});
    graph[1].edges.push_back({0, 2});
    graph[1].edges.push_back({2, 1});
    graph[1].edges.push_back({3, 7});
    graph[2].edges.push_back({0, 4});
    graph[2].edges.push_back({1, 1});
    graph[2].edges.push_back({3, 3});
    graph[3].edges.push_back({1, 7});
    graph[3].edges.push_back({2, 3});
    graph[3].edges.push_back({4, 1});
    graph[4].edges.push_back({3, 1});
    graph[4].edges.push_back({5, 5});
    graph[5].edges.push_back({4, 5});

    int startVertex = 0;
    primMST(graph, startVertex);

    return 0;
}
