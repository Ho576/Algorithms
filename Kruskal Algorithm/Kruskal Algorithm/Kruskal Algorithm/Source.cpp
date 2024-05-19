#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Compare function to sort edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Find operation of union-find
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union operation of union-find
void unionSets(vector<Subset>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Kruskal's algorithm to find MST
void kruskalMST(vector<vector<int>>& graph, int V) {
    int E = V * (V - 1) / 2; // Number of edges in a complete graph

    // Store all edges
    vector<Edge> edges;
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (graph[i][j] != 0) {
                Edge edge = { i, j, graph[i][j] };
                edges.push_back(edge);
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Initialize subsets for union-find
    vector<Subset> subsets(V);
    for (int i = 0; i < V; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    vector<Edge> result; // Stores the edges of MST
    int totalWeight = 0; // Total weight of MST

    // Iterate through sorted edges and add to MST if it doesn't form a cycle
    for (const Edge& edge : edges) {
        int x = find(subsets, edge.src);
        int y = find(subsets, edge.dest);

        if (x != y) {
            result.push_back(edge);
            totalWeight += edge.weight;
            unionSets(subsets, x, y);
        }
    }

    // Print MST edges and total weight
    cout << "Edges of Minimum Spanning Tree:" << endl;
    for (const Edge& edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }
    cout << "Total Weight of Minimum Spanning Tree: " << totalWeight << endl;
}

int main() {
    // Example graph represented using a 2D array
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int V = graph.size(); // Number of vertices

    kruskalMST(graph, V);

}
