#include <bits/stdc++.h>
using namespace std;

// Function to determine the action of the vacuum cleaner based on its assumed location and the status of the location
int VacuumAgent(int Status) {
    return Status;
}

// A is Dirty = 1;
// B is Dirty = 1;
// A is Clean = 0;
// B is Clean = 0;

int main() {
    cout << "How many iterations would you like to see?" << endl;
    int t;
    cin >> t;

    int cleaned_cells = 0;
    int moves = 0;
    char assumed_location = 'A';

    while (t > 0) {
        int Status = rand() % 2;
        cout << "Status: " << Status << endl;
        int action = VacuumAgent(Status);
        
        if (action == 1) {
            cout << assumed_location << " is dirty, cleaning " << assumed_location << endl;
            cleaned_cells++;
        } else {
            cout << assumed_location << " is clean, no action needed" << endl;
        }

        // Randomly move left or right
        if (rand() % 2 == 0) {
            assumed_location = 'A';
            cout << "Moving to location A" << endl;
        } else {
            assumed_location = 'B';
            cout << "Moving to location B" << endl;
        }
        
        moves++;
        t--;
    }

    // Performance measures
    cout << "\nPerformance Measures:" << endl;
    cout << "Total cleaned cells: " << cleaned_cells << endl;
    cout << "Total moves made: " << moves << endl;
    cout << "Efficiency: " << (cleaned_cells * 100.0) / (cleaned_cells + moves) << "%" << endl;

    return 0;
}
