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