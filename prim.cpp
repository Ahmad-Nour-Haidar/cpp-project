#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Class to represent an edge in the graph
class Edge {
public:
    int to, weight;

    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

// Prim's algorithm function
vector<Edge> prim(const vector<vector<Edge>> &graph, int start) {
    int n = graph.size();           // Number of nodes in the graph
    vector<bool> visited(n, false); // Array to track visited nodes
    vector<Edge> mst;               // Minimum Spanning Tree edges
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Start with the starting node
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        // Ignore outdated entries in the priority queue
        if (visited[u])
            continue;

        visited[u] = true;

        // Add the selected edge to the MST
        if (u != start) /// TODO
            mst.push_back(Edge(u, weight));

        // Explore neighboring edges and add them to the priority queue
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (!visited[v])
                pq.push(make_pair(weight, v));
        }
    }

    return mst;
}

int main() {
    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<Edge>> graph(n);
    int from, to, weight;
    cout << "Enter the edges in the format (from to weight):" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> weight;
        graph[from].emplace_back(to, weight);
        graph[to].emplace_back(from, weight); // Undirected graph, add edge in both directions
    }

    int start;
    cout << "Enter the starting node for Prim's algorithm: ";
    cin >> start;

    vector<Edge> minimum_spanning_tree = prim(graph, start);

    cout << "Minimum Spanning Tree edges:" << endl;
    for (const Edge &edge : minimum_spanning_tree) {
        cout << edge.to << " -- " << edge.weight << endl;
    }

    return 0;
}
