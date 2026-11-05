#include <iostream>
#include <string>
using namespace std;

struct Edge {
    int u, v, weight;
};

int parent[50];

int findSet(int x) {
    while (parent[x] != x) {
        x = parent[x];
    }
    return x;
}

int main() {
    int n, e;
    string names[50];
    Edge edges[200];

    cout << "Enter number of departments: ";
    cin >> n;
    cout << "Enter department names:\n";
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    cout << "Enter number of paths: ";
    cin >> e;
    cout << "Enter each path as: dept1_index dept2_index distance (index starts from 0)\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int totalDistance = 0, edgesUsed = 0;
    cout << "\nMinimum Spanning Tree (Kruskal):\n";
    for (int i = 0; i < e && edgesUsed < n - 1; i++) {
        int a = findSet(edges[i].u);
        int b = findSet(edges[i].v);
        if (a != b) {
            cout << names[edges[i].u] << " - " << names[edges[i].v] << " : " << edges[i].weight << "\n";
            totalDistance += edges[i].weight;
            parent[a] = b;
            edgesUsed++;
        }
    }

    if (edgesUsed != n - 1) {
        cout << "Graph is not connected\n";
    }
    cout << "Total distance: " << totalDistance << "\n";

    return 0;
}
