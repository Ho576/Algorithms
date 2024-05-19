//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//// Structure to represent an edge in the graph
//struct Edge {
//    int src, dest, weight;
//};
//
//// Structure to represent a subset for union-find
//struct Subset {
//    int parent, rank;
//};
//
//// Comparator function to sort edges by weight
//bool compareEdges(const Edge& a, const Edge& b) {
//    return a.weight < b.weight;
//}
//
//// Find operation for union-find
//int find(vector<Subset>& subsets, int i) {
//    if (subsets[i].parent != i)
//        subsets[i].parent = find(subsets, subsets[i].parent);
//    return subsets[i].parent;
//}
//
//// Union operation for union-find
//void Union(vector<Subset>& subsets, int x, int y) {
//    int xroot = find(subsets, x);
//    int yroot = find(subsets, y);
//
//    if (subsets[xroot].rank < subsets[yroot].rank)
//        subsets[xroot].parent = yroot;
//    else if (subsets[xroot].rank > subsets[yroot].rank)
//        subsets[yroot].parent = xroot;
//    else {
//        subsets[yroot].parent = xroot;
//        subsets[xroot].rank++;
//    }
//}
//
//// Function to find Minimum Spanning Tree (MST) using Kruskal's algorithm
//void KruskalMST(const vector<vector<int>>& graph, int V) {
//    vector<Edge> edges; // Store all edges
//    // Populate edges vector
//    for (int i = 0; i < V; ++i) {
//        for (int j = i + 1; j < V; ++j) {
//            if (graph[i][j] != 0) {
//                edges.push_back({ i, j, graph[i][j] });
//            }
//        }
//    }
//
//    // Sort edges by weight
//    sort(edges.begin(), edges.end(), compareEdges);
//
//    // Initialize subsets for union-find
//    vector<Subset> subsets(V);
//    for (int i = 0; i < V; ++i) {
//        subsets[i].parent = i;
//        subsets[i].rank = 0;
//    }
//
//    int mstWeight = 0; // Total weight of MST
//    vector<pair<int, int>> mstEdges; // Edges in MST
//
//    // Iterate through sorted edges
//    for (const auto& edge : edges) {
//        int srcRoot = find(subsets, edge.src);
//        int destRoot = find(subsets, edge.dest);
//
//        // If including this edge does not cause cycle, include it
//        if (srcRoot != destRoot) {
//            mstEdges.push_back({ edge.src, edge.dest });
//            mstWeight += edge.weight;
//            Union(subsets, srcRoot, destRoot);
//        }
//    }
//
//    // Print MST edges and total weight
//    cout << "Minimum Spanning Tree Edges:\n";
//    for (const auto& edge : mstEdges) {
//        cout << edge.first << " - " << edge.second << endl;
//    }
//    cout << "Total Weight of MST: " << mstWeight << endl;
//}
//
//int main() {
//    int V; // Number of vertices
//    cout << "Enter the number of vertices: ";
//    cin >> V;
//
//    // Initialize graph as 2D array
//    vector<vector<int>> graph(V, vector<int>(V));
//    cout << "Enter the weighted adjacency matrix:\n";
//    for (int i = 0; i < V; ++i) {
//        for (int j = 0; j < V; ++j) {
//            cin >> graph[i][j];
//        }
//    }
//
//    // Find and print MST using Kruskal's algorithm
//    KruskalMST(graph, V);
//
//  
//}


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Comparator function to sort edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Find operation for union-find
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union operation for union-find
void Union(vector<Subset>& subsets, int x, int y) {
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

// Function to find Minimum Spanning Tree (MST) using Kruskal's algorithm
void KruskalMST(vector<vector<int>>& graph, int V) {
    vector<Edge> edges; // Store all edges
    // Populate edges vector
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (graph[i][j] != 0) {
                edges.push_back({ i, j, graph[i][j] });
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

    int mstWeight = 0; // Total weight of MST
    vector<pair<int, int>> mstEdges; // Edges in MST

    // Iterate through sorted edges
    for (const auto& edge : edges) {
        int srcRoot = find(subsets, edge.src);
        int destRoot = find(subsets, edge.dest);

        // If including this edge does not cause cycle, include it
        if (srcRoot != destRoot) {
            mstEdges.push_back({ edge.src, edge.dest });
            mstWeight += edge.weight;
            Union(subsets, srcRoot, destRoot);
        }
    }

    // Print MST edges and total weight
    cout << "Minimum Spanning Tree Edges:\n";
    for (const auto& edge : mstEdges) {
        cout << edge.first << " - " << edge.second << endl;
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

int main() {
    // Example graph represented using a weighted adjacency matrix
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    int V = graph.size(); // Number of vertices

    // Find and print MST using Kruskal's algorithm
    KruskalMST(graph, V);

    return 0;
}

