#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int V=10) : vertices(V), adjList(V) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void topologicalSortUtil(stack<int>& st, vector<bool>& visited, vector<int>& inDegree, vector<vector<int>>& result) {
        bool flag = false;

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i] && inDegree[i] == 0) {
                for (int neighbor : adjList[i]) {
                    inDegree[neighbor]--;
                }

                st.push(i);
                visited[i] = true;
                topologicalSortUtil(st, visited, inDegree, result);

                visited[i] = false;
                st.pop();

                for (int neighbor : adjList[i]) {
                    inDegree[neighbor]++;
                }

                flag = true;
            }
        }

        if (!flag) {
            vector<int> temp;
            stack<int> tempStack = st;

            while (!tempStack.empty()) {
                temp.push_back(tempStack.top());
                tempStack.pop();
            }

            reverse(temp.begin(), temp.end());
            result.push_back(temp);
        }
    }

    void allTopologicalSorts() {
        vector<bool> visited(vertices, false);
        vector<int> inDegree(vertices, 0);

        for (int i = 0; i < vertices; ++i) {
            for (int neighbor : adjList[i]) {
                inDegree[neighbor]++;
            }
        }

        stack<int> st;
        vector<vector<int>> result;

        topologicalSortUtil(st, visited, inDegree, result);

        cout << "All possible topological sorts: "<<endl;
        for (const vector<int>& ordering : result) {
            for (int vertex : ordering) {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    g.allTopologicalSorts();

}

