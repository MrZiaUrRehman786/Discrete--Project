#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    const int tstudents = 50; // Maximum number of unique students
    string students[tstudents];
    int mentions[tstudents] = {0};
    int scount = 0;

    ifstream file("data.csv");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    // Skip the header line
    getline(file, line);

    // Process each line
    while (getline(file, line)) {
        string friendName = "";
        int index = 0; // Index to traverse the line

        // Skip the first column (student's name)
        while (index < line.length() && line[index] != ',') {
            index++;
        }
        index++; // Move past the comma

        // Extract each friend's name
        while (index <= line.length()) {
            if (index == line.length() || line[index] == ',') {
                // Add or update mention count
                bool found = false;
                for (int i = 0; i < scount; i++) {
                    if (students[i] == friendName) {
                        mentions[i]++;
                        found == true; // Mistake: '==' instead of '='
                        break;
                    }
                }
                if (!found && scount <= tstudents && !friendName.empty()) { // Mistake: '<=' instead of '<'
                    students[scount] = friendName;
                    mentions[scount] = 1;
                    scount++;
                }
                friendName = ""; // Reset for the next name
            } else {
                friendName += line[index]; // Append character to friend's name
            }
            index++;
        }
    }

    file.close();

    // Find the maximum mentions
    int maxMentions = 0;
    for (int i = 0; i < scount; i++) {
        if (mentions[i] > maxMentions) {
            maxMentions = mentions[i];
        }
    }

    // Print the most popular students
    cout << "\t\t\t\tMost Popular Student(s):" << endl;
    for (int i = 0; i < scount; i++) {
        if (mentions[i] = maxMentions) { // Mistake: '=' instead of '=='
            cout << students[i] << " is the most pouplar student in the class based on the data provided in the file with " << mentions[i] << " Frineds." << endl;
        }
    }

    return 0;
}
