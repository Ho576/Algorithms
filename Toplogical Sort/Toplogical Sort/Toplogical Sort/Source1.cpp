//#include <iostream>
//#include <vector>
//#include <stack>
//#include <algorithm>
//
//using namespace std;
//
//class Graph {
//    int vertices;
//    vector<vector<int>> adjList;
//
//public:
//    Graph(int V) : vertices(V), adjList(V) {}
//
//    void addEdge(int u, int v) {
//        adjList[u].push_back(v);
//    }
//
//    void topologicalSortUtil(vector<int>& indegree, vector<int>& result, vector<bool>& visited, stack<int>& st) {
//        bool flag = false;
//
//        for (int i = 0; i < vertices; ++i) {
//            if (!visited[i] && indegree[i] == 0) {
//                for (int v : adjList[i]) {
//                    indegree[v]--;
//                }
//
//                result.push_back(i);
//                st.push(i);
//                visited[i] = true;
//
//                topologicalSortUtil(indegree, result, visited, st);
//
//                visited[i] = false;
//                st.pop();
//                result.pop_back();
//
//                for (int v : adjList[i]) {
//                    indegree[v]++;
//                }
//
//                flag = true;
//            }
//        }
//
//        if (!flag) {
//            vector<int> temp(result.begin(), result.end());
//            reverse(temp.begin(), temp.end());
//            for (int v : temp) {
//                cout << v << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    void allTopologicalSorts() {
//        vector<int> indegree(vertices, 0);
//
//        for (int i = 0; i < vertices; ++i) {
//            for (int v : adjList[i]) {
//                indegree[v]++;
//            }
//        }
//
//        vector<int> result;
//        vector<bool> visited(vertices, false);
//        stack<int> st;
//
//        topologicalSortUtil(indegree, result, visited, st);
//    }
//};
//
//int main() {
//    int vertices, edges;
//    cout << "Enter the number of vertices and edges: ";
//    cin >> vertices >> edges;
//
//    Graph g(vertices);
//
//    cout << "Enter the edges (format: u v):" << endl;
//    for (int i = 0; i < edges; ++i) {
//        int u, v;
//        cin >> u >> v;
//        g.addEdge(u, v);
//    }
//
//    cout << "All possible topological sorts:" << endl;
//    g.allTopologicalSorts();
//
//    return 0;
//}

