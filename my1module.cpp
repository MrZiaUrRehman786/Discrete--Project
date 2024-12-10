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
                        found = true;
                        break;
                    }
                }
                if (!found && scount < tstudents && !friendName.empty()) {
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
        if (mentions[i] == maxMentions) {
            cout << students[i] << " is the most pouplar student in the class based on the data provided in the file with " << mentions[i] << " Frineds." << endl;
        }
    }

    return 0;
}






// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string.h>
// using namespace std;
// void getname(string arr1[], int TOTAL_COUNT, int STUDENT_COUNT)
// {
//     // this loop is to run for every student to check for their friendship
//     for (int i = 0; i < STUDENT_COUNT; i++)
//     {
//         // this loop moves to the friends of students
//         for (int j = i + STUDENT_COUNT; j < TOTAL_COUNT; j += STUDENT_COUNT)
//         {
//             // this loop check if the friend of student has also add friends
//             for (int k = 0; k < STUDENT_COUNT; k++)
//             {
//                 // if the friend has added his friends
//                 if (arr1[k] == arr1[j])
//                 {
//                     bool asymmetric = true;
//                     // this loop checks if the friend of student has also added the student in his friend list
//                     for (int l = k + STUDENT_COUNT; l < TOTAL_COUNT; l += STUDENT_COUNT)
//                     {
//                         if (arr1[l] == arr1[i])
//                         {                       // this condition check if he has added or not
//                             asymmetric = false; // if he added him then their relation is not asymmetric
//                         }
//                         // cout<<arr1[l]<<endl;
//                     }
//                     if (asymmetric == true)
//                     { // check the student is asymetric to how many of his friends
//                         cout << arr1[i] << " is asymmetric with " << arr1[k] << endl;
//                     }
//                 }
//             }

//         }
//     }
// }

// int main()
// {
//     // first initinalize students name than add their friends name
//     int const TOTAL_COUNT = 240;
//     string arr1[TOTAL_COUNT];
//     // total number of students
//     int const STUDENT_COUNT = 40;

//     int count = 0;
//     ifstream file("data.csv");
//     if (file.is_open())
//     {
//         string line;

//         while (getline(file, line) && count < TOTAL_COUNT)
//         {
//             stringstream ss(line);
//             string item;

//             // Tokenize the line by comma and store in the array
//             while (getline(ss, item, ',') && count < TOTAL_COUNT)
//             {
//                 arr1[count++] = item;
//             }
//         }
//         file.close();
//     }
//     else
//     {
//         cout << "Unable to open file" << endl;
//         return 1;
//     }
//     getname(arr1, TOTAL_COUNT, STUDENT_COUNT);
//     return 0;
// }
