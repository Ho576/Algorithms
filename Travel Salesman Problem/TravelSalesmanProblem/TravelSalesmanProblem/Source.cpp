#include <iostream>
#include <vector>

using namespace std;

// Function to create an adjacency matrix
vector<vector<int>> create_adjacency_matrix(int vertices, vector<pair<int, int>>& edges) {
    // Create an empty adjacency matrix filled with zeros
    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    // Fill the adjacency matrix based on the edges
    for (const auto& edge : edges) {
        int start = edge.first;
        int end = edge.second;
        adjacency_matrix[start][end] = 1;
    }

    return adjacency_matrix;
}

// Function to compute the reduced matrix
vector<vector<int>> compute_reduced_matrix(const vector<vector<int>>& adjacency_matrix) {
    // Deep copy the adjacency matrix
    vector<vector<int>> reduced_matrix = adjacency_matrix;

    // Compute the reduced matrix
    for (size_t k = 0; k < reduced_matrix.size(); ++k) {
        for (size_t i = 0; i < reduced_matrix.size(); ++i) {
            for (size_t j = 0; j < reduced_matrix.size(); ++j) {
                reduced_matrix[i][j] |= reduced_matrix[i][k] & reduced_matrix[k][j];
            }
        }
    }

    return reduced_matrix;
}

// Function to calculate the sum of differences
int sum_of_differences(const vector<vector<int>>& original_matrix, const vector<vector<int>>& reduced_matrix) {
    // Compute the sum of differences
    int sum_diff = 0;
    for (size_t i = 0; i < original_matrix.size(); ++i) {
        for (size_t j = 0; j < original_matrix.size(); ++j) {
            sum_diff += original_matrix[i][j] - reduced_matrix[i][j];
        }
    }

    return sum_diff;
}

int main() {
    int vertices = 4;
    vector<pair<int, int>> edges = { {0, 1}, {1, 2}, {2, 3}, {3, 0} };  // Example strongly connected graph

    vector<vector<int>> adjacency_matrix = create_adjacency_matrix(vertices, edges);
    cout << "Original Adjacency Matrix:" << endl;
    for (const auto& row : adjacency_matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vector<int>> reduced_matrix = compute_reduced_matrix(adjacency_matrix);
    cout << "\nReduced Adjacency Matrix:" << endl;
    for (const auto& row : reduced_matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    int sum_diff = sum_of_differences(adjacency_matrix, reduced_matrix);
    cout << "\nSum of Differences: " << sum_diff << endl;

 
}
