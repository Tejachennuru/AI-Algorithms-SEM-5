#include <iostream>
using namespace std;

enum LocationStatus { CLEAN, DIRTY };

struct WorldState {
    LocationStatus locationA;
    LocationStatus locationB;
    char agentLocation;
};

class VacuumAgent {
public:
    void UpdateWorldState(WorldState &state, char location, LocationStatus status) {
        if (location == 'A') state.locationA = status;
        if (location == 'B') state.locationB = status;
    }

    void Act(WorldState &state) {
        if (state.agentLocation == 'A') {
            if (state.locationA == DIRTY) {
                cout << "A is Dirty, Cleaning A." << endl;
                state.locationA = CLEAN;
            } else {
                cout << "A is Clean, Moving to B." << endl;
                state.agentLocation = 'B';
            }
        } else if (state.agentLocation == 'B') {
            if (state.locationB == DIRTY) {
                cout << "B is Dirty, Cleaning B." << endl;
                state.locationB = CLEAN;
            } else {
                cout << "B is Clean, Moving to A." << endl;
                state.agentLocation = 'A';
            }
        }
    }
};

int main() {
    VacuumAgent agent;
    WorldState state = {DIRTY, DIRTY, 'A'};

    cout << "Enter the number of iterations: ";
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        agent.Act(state);
    }

    return 0;
}
