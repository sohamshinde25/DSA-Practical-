#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, e;
    string names[50];
    int graph[50][50];

    cout << "Enter number of departments: ";
    cin >> n;
    cout << "Enter department names:\n";
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    cout << "Enter number of paths: ";
    cin >> e;
    cout << "Enter each path as: dept1_index dept2_index distance (index starts from 0)\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    bool visited[50];
    int key[50], parent[50];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        key[i] = 1000000;
        parent[i] = -1;
    }
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        if (key[u] == 1000000) {
            cout << "Graph is not connected\n";
            break;
        }

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !visited[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int totalDistance = 0;
    cout << "\nMinimum Spanning Tree (Prim):\n";
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            cout << names[parent[i]] << " - " << names[i] << " : " << graph[parent[i]][i] << "\n";
            totalDistance += graph[parent[i]][i];
        }
    }
    cout << "Total distance: " << totalDistance << "\n";

    return 0;
}
