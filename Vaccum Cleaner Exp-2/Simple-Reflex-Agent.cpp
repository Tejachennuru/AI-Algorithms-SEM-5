#include <bits/stdc++.h>
using namespace std;


int VacuumAgent(char Location, int Status){
    if(Location == 'A' && Status == 0) return 0;
    if(Location == 'B' && Status == 0) return 1;
    if(Location == 'A' && Status == 1) return 2;
    if(Location == 'B' && Status == 1) return 3;
}

// A is Dirty = 1;
// B is Dirty = 1;
// A is Clean = 0;
// B is Clean = 0;


int main(){
    cout << "How many Iteration You would like to see ?" << endl;
    int t;
    cin >> t;
    cout << "Start with Location A" << endl;
    char Location = 'A';
    while(t > 0){
        int Status = rand() % 2;
        cout << "Status :" << Status << " " << endl;
        int n = VacuumAgent(Location, Status);
        switch(n){
            case -1: cout << "exiting" << endl;
                     exit(0);
            case 0: cout << "A is Clean, Move Right" << endl;
                    Location = 'B';
                    break;
            case 1: cout << "B is Clean, Move Left" << endl;
                    Location = 'A';
                    break;
            case 2: cout << "A is Dirty, A is cleaner and Move Right "<< endl;
                    Location = 'B';
                    break;
            case 3: cout << "B is Dirty, B is cleaned and Move Left"<< endl;
                    Location = 'A';
                    break;
            default: cout << "Enter valid Input"<< endl ;
                    break;

        }
        t--;
    }

}