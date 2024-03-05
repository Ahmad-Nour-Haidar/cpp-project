/**/
#include <bits/stdc++.h>

using namespace std;

/*
 * Ahmad Nour Haidar
 *
 * MST: Minimum spanning tree - Kruskal's algorithm
 * Note: A graph can have more than one (MST).
 *
 * */

/// DSU:
class DSU {
private:
    int *parent; /// pointer to array
    int *size;   /// pointer to array
    int length;

public:
    /// constructor
    DSU(int length) {
        this->length = length;
        parent = new int[length]; /// initial pointer
        size = new int[length];   /// initial pointer

        for (int i = 0; i < length; ++i) {
            parent[i] = i;
            size[i] = 1;
        }
    }

//    void make_set(int v) {
//        parent[v] = v;
//        size[v] = 1;
//    }

    int find_set(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = find_set(parent[x]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) {
                swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
        }
    }

    /// end class DSU.
};


/// Kruskal:
/// Time Complexity: O(E * logE) or O(E * logV)
/// Auxiliary Space: O(V + E)
class Kruskal {
private:
    struct Edge {
        /// edge: (x) <--w--> (y)
        int x, y, weight;

        /// constructor
        Edge(int x, int y, int weight) : x(x), y(y), weight(weight) {}

        /// this function is used to compare two edges.
        bool operator<(const Edge &other) const {
            if (weight not_eq other.weight) {
                return weight < other.weight;
            }
            if (x not_eq other.x) {
                return x < other.x;
            }
            return y < other.y;
        }

        /// end struct Edge.
    };

    /// this function is used for sorting edges.
    /// sorting edges from min weight to height weight.
    static bool compareTwoEdges(const Edge &a, const Edge &b) {
        return a < b;
    }

    int number; /// number of edges.
    vector<Edge> edges; /// to store all edges

    static void print_edge(const Edge &node) {
        cout << node.x << " <--> " << node.y << " = " << node.weight << '\n';
    };

public:
    /// constructor
    Kruskal(int number) : number(number) {}

    void add_edge(const int &x, const int &y, const int &weight) {
        edges.emplace_back(x, y, weight);
    }

    void kruskal_mst() {

        DSU dsu(number);

        /// sort:
        /// Time Complexity: O(E * logE)
        sort(edges.begin(), edges.end(), compareTwoEdges);

        int total_weight = 0;

        for (Edge edge : edges) {
            int set_x = dsu.find_set(edge.x);
            int set_y = dsu.find_set(edge.y);
            if (set_x not_eq set_y) {
                dsu.union_sets(edge.x, edge.y);
                total_weight += edge.weight;
                print_edge(edge);
            }
        }

        cout << "\nMinimum total cost of your graph = " << total_weight << endl;
    }

    /// end class Kruskal;
};


int main() {

    int number_nodes = 10;
    //    int number_edges = 14;
    //    cout << "enter number nodes:";
    //    cin >> number_nodes;
    //    cout << "enter number edges:";
    //    cin >> number_edges;


    Kruskal kruskal(number_nodes);

    kruskal.add_edge(0, 1, 4);
    kruskal.add_edge(0, 7, 8);
    kruskal.add_edge(1, 7, 11);
    kruskal.add_edge(1, 2, 8);
    kruskal.add_edge(2, 5, 4);
    kruskal.add_edge(2, 8, 2);
    kruskal.add_edge(2, 3, 7);
    kruskal.add_edge(3, 5, 14);
    kruskal.add_edge(3, 4, 9);
    kruskal.add_edge(4, 5, 10);
    kruskal.add_edge(5, 6, 2);
    kruskal.add_edge(6, 8, 6);
    kruskal.add_edge(6, 7, 1);
    kruskal.add_edge(7, 8, 7);

    kruskal.kruskal_mst();


    return 0;
}

/*
 * 9 14
0 1 4
0 7 8
1 7 11
1 2 8
2 8 2
2 3 7
2 5 4
3 5 14
3 4 9
4 5 10
5 6 2
6 8 6
6 7 1
7 8 7
 * */