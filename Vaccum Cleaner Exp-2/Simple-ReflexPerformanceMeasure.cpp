#include <bits/stdc++.h>
using namespace std;

// Function to determine the action of the vacuum cleaner based on its location and the status of the location
int VacuumAgent(char Location, int Status) {
    if (Location == 'A' && Status == 0) return 0;
    if (Location == 'B' && Status == 0) return 1;
    if (Location == 'A' && Status == 1) return 2;
    if (Location == 'B' && Status == 1) return 3;
}

// A is Dirty = 1;
// B is Dirty = 1;
// A is Clean = 0;
// B is Clean = 0;

int main() {
    cout << "How many iterations would you like to see?" << endl;
    int t;
    cin >> t;
    cout << "Start with Location A" << endl;

    char Location = 'A';
    int cleaned_cells = 0;
    int moves = 0;

    while (t > 0) {
        int Status = rand() % 2;
        cout << "Status: " << Status << endl;
        int action = VacuumAgent(Location, Status);
        switch (action) {
            case -1:
                cout << "Exiting" << endl;
                exit(0);
            case 0:
                cout << "A is clean, move right" << endl;
                Location = 'B';
                moves++;
                break;
            case 1:
                cout << "B is clean, move left" << endl;
                Location = 'A';
                moves++;
                break;
            case 2:
                cout << "A is dirty, A is cleaned, and move right" << endl;
                Location = 'B';
                cleaned_cells++;
                moves++;
                break;
            case 3:
                cout << "B is dirty, B is cleaned, and move left" << endl;
                Location = 'A';
                cleaned_cells++;
                moves++;
                break;
            default:
                cout << "Enter valid input" << endl;
                break;
        }
        t--;
    }

    // Performance measures
    cout << "\nPerformance Measures:" << endl;
    cout << "Total cleaned cells: " << cleaned_cells << endl;
    cout << "Total moves made: " << moves << endl;
    cout << "Efficiency: " << (cleaned_cells * 100.0) / (cleaned_cells + moves) << "%" << endl;

    return 0;
}
