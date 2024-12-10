#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    const int tstudents = 50; 
    string students[tstudents];
    int mentions[tstudents] = {0};
    int scount = 0;

    ifstream file("data.csv");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }



   
}








