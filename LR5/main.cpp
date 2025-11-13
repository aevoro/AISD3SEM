#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <windows.h>

using namespace std;

struct Edge {
    int u, v;
    int weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

vector<Edge> kruskal_mst(int num_vertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(num_vertices);
    vector<Edge> mst_edges;
    long long total_weight = 0;

    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            mst_edges.push_back(edge);
            dsu.unite(edge.u, edge.v);
            total_weight += edge.weight;
        }
    }

    cout << "Суммарный вес МОД (Алгоритм Краскала): " << total_weight << endl;
    return mst_edges;
}

vector<Edge> prim_mst(int num_vertices, const vector<Edge>& edges) {
    vector<vector<pair<int, int>>> adj(num_vertices + 1);
    for (const auto& edge : edges) {
        adj[edge.u].push_back({edge.v, edge.weight});
        adj[edge.v].push_back({edge.u, edge.weight});
    }

    set<tuple<int, int, int>> pq;

    vector<bool> visited(num_vertices + 1, false);

    int start_node = 1;
    visited[start_node] = true;

    for (const auto& neighbor : adj[start_node]) {
        int v = neighbor.first;
        int weight = neighbor.second;
        pq.insert({weight, start_node, v});
    }

    vector<Edge> mst_edges;
    long long total_weight = 0;

    while (!pq.empty() && mst_edges.size() < num_vertices - 1) {
        auto min_edge = *pq.begin();
        pq.erase(pq.begin());

        int weight = get<0>(min_edge);
        int u = get<1>(min_edge);
        int v = get<2>(min_edge);

        if (visited[v]) continue;

        visited[v] = true;
        mst_edges.push_back({u, v, weight});
        total_weight += weight;

        for (const auto& neighbor : adj[v]) {
            int next_v = neighbor.first;
            int next_weight = neighbor.second;
            if (!visited[next_v]) {
                pq.insert({next_weight, v, next_v});
            }
        }
    }

    cout << "Суммарный вес МОД (Алгоритм Прима): " << total_weight << endl;
    return mst_edges;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    const int NUM_VERTICES = 8;

    // v1: (v2, 2), (v4, 8), (v5, 2)
    // v2: (v1, 2), (v3, 3), (v5, 5), (v4, 10)
    // v3: (v2, 3), (v5, 12), (v8, 7)
    // v4: (v1, 8), (v6, 3), (v7, 1), (v2, 10), (v5, 14)
    // v5: (v1, 2), (v2, 5), (v3, 12), (v4, 14), (v7, 4), (v8, 8), (v6, 11)
    // v6: (v4, 3), (v7, 6), (v5, 11)
    // v7: (v4, 1), (v6, 6), (v5, 4), (v8, 9)
    // v8: (v3, 7), (v5, 8), (v7, 9)

    vector<Edge> final_edges = {
        {1, 2, 2}, {1, 4, 8}, {1, 5, 2},
        {2, 3, 3}, {2, 5, 5}, {2, 4, 10},
        {3, 5, 12}, {3, 8, 7},
        {4, 6, 3}, {4, 7, 1}, {4, 5, 14},
        {5, 7, 4}, {5, 8, 8}, {5, 6, 11},
        {6, 7, 6},
        {7, 8, 9}
    };

    cout << "Алгоритм Прима" << endl;
    vector<Edge> prim_result = prim_mst(NUM_VERTICES, final_edges);

    cout << "Список ребер МОД:" << endl;
    for (const auto& edge : prim_result) {
        cout << "(v" << edge.u << ", v" << edge.v << "): " << edge.weight << endl;
    }

    cout << "Алгоритм Краскала" << endl;
    vector<Edge> kruskal_result = kruskal_mst(NUM_VERTICES, final_edges);

    cout << "Список ребер МОД:" << endl;
    for (const auto& edge : kruskal_result) {
        cout << "(v" << edge.u << ", v" << edge.v << "): " << edge.weight << endl;
    }

    return 0;
}