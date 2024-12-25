#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 50;  
const int MAX_FRIENDS = 5;    
 
void loadStudentData(const string &fileName, string studentData[MAX_STUDENTS][MAX_FRIENDS + 1], int &totalStudents) {
    ifstream inputFile(fileName.c_str());
    totalStudents = 0;

    if (!inputFile) {
        cout << "Error: Could not open file \"" << fileName << "\"\n";
        return;
    }

    string line;
    while (getline(inputFile, line) && totalStudents < MAX_STUDENTS) {
        int column = 0, start = 0;
        for (size_t i = 0; i <= line.size(); i++) {
            if (line[i] == ',' || i == line.size()) {
                studentData[totalStudents][column++] = line.substr(start, i - start);
                start = i + 1;
                if (column > MAX_FRIENDS) break;  
            }
        }
        totalStudents++;
    }

    inputFile.close();
}

 
int findCommonFriends(const string studentData[MAX_STUDENTS][MAX_FRIENDS + 1], int studentA, int studentB) {
    int commonFriends = 0;

    for (int friendA = 1; friendA <= MAX_FRIENDS; friendA++) {
        if (studentData[studentA][friendA] == "") continue;

        for (int friendB = 1; friendB <= MAX_FRIENDS; friendB++) {
            if (studentData[studentB][friendB] == "") continue;

            if (studentData[studentA][friendA] == studentData[studentB][friendB]) {
                commonFriends++;
                break;
            }
        }
    }

    return commonFriends;
}
 
void buildFriendshipGraph(const string studentData[MAX_STUDENTS][MAX_FRIENDS + 1], int totalStudents, int friendshipGraph[MAX_STUDENTS][MAX_STUDENTS]) {
    for (int i = 0; i < totalStudents; i++) {
        for (int j = 0; j < totalStudents; j++) {
            if (i != j) {
                friendshipGraph[i][j] = findCommonFriends(studentData, i, j);
            } else {
                friendshipGraph[i][j] = 0;  
            }
        }
    }
}

 
void showFriendshipGraph(const int friendshipGraph[MAX_STUDENTS][MAX_STUDENTS], int totalStudents, const string studentData[MAX_STUDENTS][MAX_FRIENDS + 1]) {
    cout << "Friendship Connections:\n";
    for (int i = 0; i < totalStudents; i++) {
        for (int j = 0; j < totalStudents; j++) {
            if (friendshipGraph[i][j] > 0) {
                cout << studentData[i][0] << " and " << studentData[j][0]
                     << " have " << friendshipGraph[i][j] << " mutual friends.\n";
            }
        }
    }
}

 
void suggestNewFriends(const string studentData[MAX_STUDENTS][MAX_FRIENDS + 1], int totalStudents, const int friendshipGraph[MAX_STUDENTS][MAX_STUDENTS], int threshold) {
    cout << "\nPotential New Friendships (Threshold: " << threshold << " mutual friends):\n";
    for (int i = 0; i < totalStudents; i++) {
        for (int j = 0; j < totalStudents; j++) {
            if (i != j && friendshipGraph[i][j] >= threshold) {
              
                bool alreadyFriends = false;
                for (int k = 1; k <= MAX_FRIENDS; k++) {
                    if (studentData[i][k] == "") break;
                    if (studentData[i][k] == studentData[j][0]) {
                        alreadyFriends = true;
                        break;
                    }
                }

                if (!alreadyFriends) {
                    cout << studentData[i][0] << " might become friends with " << studentData[j][0]
                         << " (Shared Friends: " << friendshipGraph[i][j] << ")\n";
                }
            }
        }
    }
}

int main() {
    string fileName = "data.csv";
    string studentData[MAX_STUDENTS][MAX_FRIENDS + 1];  
    int totalStudents;

   
    loadStudentData(fileName, studentData, totalStudents);

    if (totalStudents == 0) {
        cout << "No data found. Exiting program.\n";
        return 0;
    }

     
    int friendshipGraph[MAX_STUDENTS][MAX_STUDENTS];
    buildFriendshipGraph(studentData, totalStudents, friendshipGraph);

     
    showFriendshipGraph(friendshipGraph, totalStudents, studentData);

    
    int threshold = 3;  
    suggestNewFriends(studentData, totalStudents, friendshipGraph, threshold);

    return 0;
}
