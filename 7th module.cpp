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
string line;
    int index = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string person;
        getline(ss, person, ',');

        int personIndex = -1;
        for (int i = 0; i <= index; i++) {
            if (names[i] == person) {
                personIndex = i;
                break;
            }
        }
        if (personIndex == -1) {
            names[index] = person;
            personIndex = index++;
        }

      
        string friendName;
        while (getline(ss, friendName, ',')) {
            int friendIndex = -1;

       
            for (int i = 0; i < index; i++) {
                if (names[i] == friendName) {
                    friendIndex = i;
                    break;
                }
            }

            if (friendIndex == -1) {
                names[index] = friendName;
                friendIndex = index++;
            }

           
            addEdge(personIndex, friendIndex);
        }
    }

    numStudents = index;
    file.close();
}

int main() {
    const char *filename = "data.csv"; 
    loadGraphFromCSV(filename);


    findBroadcastPoints();

    return 0;
}
