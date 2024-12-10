  #include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    const int MAX_ROWS = 250;  
    const int MAX_COLS = 6;  
    string records[MAX_ROWS][MAX_COLS];
    string line;
    int currentRow = 0;

     
    ifstream inputFile("data.csv");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file!" << endl;
        return 1;
    }

  
    while (getline(inputFile, line) && currentRow < MAX_ROWS) {
        stringstream lineStream(line);
        string field;
        int currentCol = 0;
 
        while (getline(lineStream, field, ',') && currentCol < MAX_COLS) {
            records[currentRow][currentCol] = field;
            currentCol++;
        }
        currentRow++;
    }

    inputFile.close();
 
    cout << "Asymmetric Relationships:\n";
    for (int i = 1; i < currentRow; i++) {  
        string person = records[i][0];

       
        for (int j = 1; j < MAX_COLS && !records[i][j].empty(); j++) {
            string friendName = records[i][j];
            bool isDuplicatePair = false;

             
            for (int k = 1; k < currentRow; k++) {
                for (int l = 1; l < MAX_COLS && !records[k][l].empty(); l++) {
                    if (records[k][0] == friendName && records[k][l] == person) {
                        isDuplicatePair = true;
                        break;
                    }
                }
                if (isDuplicatePair) break;
            } 
            if (!isDuplicatePair) {
                cout << person << " - " << friendName << endl;
            }
        }
    }

    return 0;
}
