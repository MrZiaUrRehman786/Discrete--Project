 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    const int tstudents = 50;
    string students[tstudents];
    int matrix[tstudents][tstudents] = {0};
    int scount = 0;

    ifstream file("data.csv");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    getline(file, line);


    while (getline(file, line)) {
        string studentName = "";
        string friendName = "";
        int index = 0;

        // Extract the student's name (first column)
        while (index < line.length() && line[index] != ',') {
            studentName += line[index];
            index++;
        }
        index++;
        int studentIdx = -1;
        for (int i = 0; i < scount; i++) {
            if (students[i] == studentName) {
                studentIdx = i;
                break;
            }
        }
        if (studentIdx == -1 && scount < tstudents) {
            students[scount] = studentName;
            studentIdx = scount;
            scount++;
        }

        while (index <= line.length()) {
            if (index == line.length() || line[index] == ',') {
                if (!friendName.empty()) {

                    int friendIdx = -1;
                    for (int i = 0; i < scount; i++) {
                        if (students[i] == friendName) {
                            friendIdx = i;
                            break;
                        }
                    }
                    if (friendIdx == -1 && scount < tstudents) {
                        students[scount] = friendName;
                        friendIdx = scount;
                        scount++;
                    }
                         if (studentIdx != -1 && friendIdx != -1) {
                        matrix[studentIdx][friendIdx] = 1;
                    }
                }
                friendName = "";
            } else {
                friendName += line[index];
            }
            index++;
        }
    }

    file.close();


    int mentions[tstudents] = {0};
    for (int i = 0; i < scount; i++) {
        for (int j = 0; j < scount; j++) {
            mentions[j] += matrix[i][j];
        }
    }


    int maxMentions = 0;
    for (int i = 0; i < scount; i++) {
        if (mentions[i] > maxMentions) {
            maxMentions = mentions[i];
        }
    }


    cout << "\t\t\t\tMost Popular Student(s):" << endl;
    for (int i = 0; i < scount; i++) {
        if (mentions[i] == maxMentions) {
            cout << students[i] << " is the most popular student in the class based on the data provided in the file with " << mentions[i] << " friends." << endl;
        }
    }

    return 0;
}
