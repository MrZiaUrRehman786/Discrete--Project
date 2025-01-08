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