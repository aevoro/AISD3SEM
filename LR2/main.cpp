#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <windows.h>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int>> adjacencyMatrix;
    vector<list<int>> adjacencyList;
    vector<pair<int, int>> edgeList;

    Graph(int v) : vertices(v) {
        adjacencyMatrix.resize(v, vector<int>(v, 0));
        adjacencyList.resize(v);
    }

    vector<int> BFS_matrix(int start) {
        vector<int> result;
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);

            for (int i = 0; i < vertices; i++) {
                if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        return result;
    }

    vector<int> DFS_matrix(int start) {
        vector<int> result;
        vector<bool> visited(vertices, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                result.push_back(current);

                for (int i = vertices - 1; i >= 0; i--) {
                    if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                        s.push(i);
                    }
                }
            }
        }

        return result;
    }

    vector<int> BFS_list(int start) {
        vector<int> result;
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);

            for (auto neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return result;
    }

    vector<int> DFS_list(int start) {
        vector<int> result;
        vector<bool> visited(vertices, false);
        stack<int> s;

        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                result.push_back(current);

                for (auto it = adjacencyList[current].rbegin(); it != adjacencyList[current].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }

        return result;
    }

    void printGraphInfo() {
        cout << "Матрица смежности:" << endl;
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nСписок смежности:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << i + 1 << ": ";
            for (auto neighbor : adjacencyList[i]) {
                cout << neighbor + 1 << " ";
            }
            cout << endl;
        }

        cout << "\nСписок рёбер:" << endl;
        for (auto edge : edgeList) {
            cout << "(" << edge.first + 1 << ", " << edge.second + 1 << ") ";
        }
        cout << endl;
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Graph graph(10);

    graph.adjacencyMatrix = {
        {0,1,0,0,1,0,0,0,0,0},
        {1,0,0,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,0,1,0},
        {1,0,0,0,0,1,0,0,0,0},
        {0,0,0,1,1,0,0,0,1,0},
        {0,1,0,0,0,0,0,1,0,0},
        {0,1,1,0,0,0,1,0,0,0},
        {0,0,0,1,0,1,0,0,0,1},
        {0,0,0,0,0,0,0,0,1,0}
    };

    graph.adjacencyList = {
        {1,4},
        {0,6,7},
        {7},
        {5,8},
        {0,5},
        {3,4,8},
        {1,7},
        {1,2,6},
        {3,5,9},
        {8}
    };

    graph.edgeList = {
        {0,1}, {0,4}, {1,6}, {1,7}, {2,7},
        {3,5}, {3,8}, {4,5}, {5,8}, {6,7}, {8,9}
    };

    cout << "Информация о графе" << endl;
    graph.printGraphInfo();

    cout << "\nРезультаты поиска" << endl;
я
    vector<int> bfs_matrix = graph.BFS_matrix(0);
    cout << "BFS (матрица смежности): ";
    for (int v : bfs_matrix) cout << v + 1 << " ";
    cout << endl;

    vector<int> dfs_matrix = graph.DFS_matrix(0);
    cout << "DFS (матрица смежности): ";
    for (int v : dfs_matrix) cout << v + 1 << " ";
    cout << endl;

    vector<int> bfs_list = graph.BFS_list(0);
    cout << "BFS (список смежности): ";
    for (int v : bfs_list) cout << v + 1 << " ";
    cout << endl;

    vector<int> dfs_list = graph.DFS_list(0);
    cout << "DFS (список смежности): ";
    for (int v : dfs_list) cout << v + 1 << " ";
    cout << endl;

    return 0;
}