#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 50; 
const int MAX_FRIENDS = 5; 

void loadData(const string &filename, string data[MAX_STUDENTS][MAX_FRIENDS + 1], int &rowCount) {
    ifstream file("data.csv");
    rowCount = 0;

    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line) && rowCount < MAX_STUDENTS) {
        size_t start = 0, end = 0, col = 0;
        while ((end = line.find(',', start)) != string::npos && col <= MAX_FRIENDS) {
            data[rowCount][col++] = line.substr(start, end - start);
            start = end + 1;
        }
        if (col <= MAX_FRIENDS) {
            data[rowCount][col] = line.substr(start);         }
        rowCount++;
    }

    file.close();
}
int countCommonFriends(const string data[MAX_STUDENTS][MAX_FRIENDS + 1], int student1, int student2) {
    int commonCount = 0;

    for (int i = 1; i <= MAX_FRIENDS; i++) {
        if (data[student1][i].empty()) continue;  

        for (int j = 1; j <= MAX_FRIENDS; j++) {
            if (data[student2][j].empty()) continue;  // Skip empty entries

            if (data[student1][i] == data[student2][j]) {
                commonCount++;
                break; 
            }
        }
    }

    return commonCount;
}

void createMultiplicityGraph(const string data[MAX_STUDENTS][MAX_FRIENDS + 1], int rowCount, int graph[MAX_STUDENTS][MAX_STUDENTS]) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            if (i != j) {
                graph[i][j] = countCommonFriends(data, i, j);
            } else {
                graph[i][j] = 0;
            }
        }
    }
}

void displayGraph(const int graph[MAX_STUDENTS][MAX_STUDENTS], int rowCount, const string data[MAX_STUDENTS][MAX_FRIENDS + 1]) {
    cout << "Multiplicity Graph (Weighted Edges):\n";
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            if (graph[i][j] > 0) {
                cout << data[i][0] << " -> " << data[j][0]
                     << " [Weight: " << graph[i][j] << "]\n";
            }
        }
    }
}

int main() {
    string filename = "data.csv";
    string data[MAX_STUDENTS][MAX_FRIENDS + 1];  // 2D array to store data
    int rowCount;
    
    loadData(filename, data, rowCount);

    if (rowCount == 0) {
        cout << "No data loaded. Exiting...\n";
        return 0;
    }

    int graph[MAX_STUDENTS][MAX_STUDENTS];
    createMultiplicityGraph(data, rowCount, graph);

    displayGraph(graph, rowCount, data);

    return 0;
}
