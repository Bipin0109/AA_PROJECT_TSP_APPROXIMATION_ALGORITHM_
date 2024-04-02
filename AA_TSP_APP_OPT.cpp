#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <climits>
using namespace std;
const int V = 5;
vector<int>final_ans;
vector<vector<int>> primMST(vector<vector<int>>& graph) {
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        mstSet[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                pq.push({key[v], v});
            }
        }
    }

    vector<vector<int>> mst;
    for (int i = 1; i < V; ++i) {
        mst.push_back({parent[i], i});
    }
    return mst;
}

void DFS(vector<vector<int>>& graph, int v, bitset<V>& visited) {
    visited[v] = true;
    final_ans.push_back(v);

    for (int u = 0; u < V; ++u) {
        if (!visited[u] && graph[v][u]) {
            DFS(graph, u, visited);
        }
    }
}

int main() {
    vector<vector<int>> graph = {{0, 10, 18, 40, 20},
                                  {10, 0, 35, 15, 12},
                                  {18, 35, 0, 25, 25},
                                  {40, 15, 25, 0, 30},
                                  {20, 12, 25, 30, 0}};

    vector<vector<int>> mst = primMST(graph);
    vector<vector<int>> adjacency_list(V, vector<int>(V, 0));
    for (auto& edge : mst) {
        adjacency_list[edge[0]][edge[1]] = 1;
        adjacency_list[edge[1]][edge[0]] = 1;
    }

    bitset<V> visited;
    DFS(adjacency_list, 0, visited);
    final_ans.push_back(0);

    for (int vertex : final_ans) cout << vertex << " -> ";
    cout << endl;
    return 0;
}

