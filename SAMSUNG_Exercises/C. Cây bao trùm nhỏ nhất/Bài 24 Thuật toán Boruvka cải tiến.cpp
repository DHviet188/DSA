#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc cạnh
struct Edge {
    int src, dest, weight;
};

// Định nghĩa cấu trúc đỉnh của cây bao trùm nhỏ nhất
struct Node {
    int parent, rank;
};

struct Graph {
    int V, E;
    vector<Edge> edges;

    // Constructor
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }
};

int findRoot(Node nodes[], int u) {
    while (nodes[u].parent != u) {
        nodes[u].parent = nodes[nodes[u].parent].parent; // Path compression
        u = nodes[u].parent;
    }
    return u;
}

void mergeTrees(Node nodes[], int u, int v) {
    int rootU = findRoot(nodes, u);
    int rootV = findRoot(nodes, v);

    nodes[rootV].parent = rootU;
}

void boruvkaMST(Graph graph) {
    int V = graph.V, E = graph.E;

    Node *nodes = new Node[V];
    for (int i = 0; i < V; i++) {
        nodes[i].parent = i;
        nodes[i].rank = 0;
    }

    // Lặp cho đến khi chỉ còn một cây
    while (V > 1) {
        int *cheapest = new int[V];
        fill(cheapest, cheapest + V, INT_MAX);

        for (int i = 0; i < E; i++) {
            int set1 = findRoot(nodes, graph.edges[i].src);
            int set2 = findRoot(nodes, graph.edges[i].dest);

            if (set1 != set2) {
                int weight = graph.edges[i].weight;
                if (cheapest[set1] == INT_MAX || cheapest[set1] > weight)
                    cheapest[set1] = weight;

                if (cheapest[set2] == INT_MAX || cheapest[set2] > weight)
                    cheapest[set2] = weight;
            }
        }

        for (int i = 0; i < V; i++) {
            if (cheapest[i] != INT_MAX) {
                int root = findRoot(nodes, i);
                if (cheapest[root] != INT_MAX) {
                    cout << "Edge " << i << " - " << nodes[i].parent << " Weight " << cheapest[i] << endl;
                    mergeTrees(nodes, i, nodes[i].parent);
                    V--;
                }
            }
        }

        delete[] cheapest;
    }
}

int main() {
    int V = 4, E = 5;
    Graph graph(V, E);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    boruvkaMST(graph);

    return 0;
}
