#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

const int MAX = 100; 
int adj[MAX][MAX] = {0}; 
int transposedAdj[MAX][MAX] = {0}; 

int numStudents = 0;  
string names[MAX];      
void addEdge(int u, int v) 
{
    adj[u][v] = 1; 
    transposedAdj[v][u] = 1; 
}

int DFS(int src, bool visited[MAX], int adjMatrix[MAX][MAX]) 
{
    visited[src] = true;
    int reachable = 1; 

    for (int i = 0; i < numStudents; i++)
 {
        if (adjMatrix[src][i] == 1 && !visited[i])
 {
            reachable += DFS(i, visited, adjMatrix); 
        }
    }
    return reachable;
}

void findBroadcastPoints() {
    cout << "Broadcast Points:\n";
    bool found = false;
    for (int i = 0; i < numStudents; i++) {
        bool visited[MAX] = {false};

        int reachableFromI = DFS(i, visited, adj);

        if (reachableFromI == numStudents) {
                   bool visitedReverse[MAX] = {false};
            int reachableInReverse = DFS(i, visitedReverse, transposedAdj);

            if (reachableInReverse == numStudents) {
                cout << names[i] << " is a broadcast point.\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No broadcast points found.\n";
    }
}
void loadGraphFromCSV(const char *filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file.\n";
        return;
    }
