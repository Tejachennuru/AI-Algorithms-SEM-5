#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum LocationStatus { CLEAN, DIRTY };

struct WorldState {
    LocationStatus locationA;
    LocationStatus locationB;
    char agentLocation;
};

class VacuumAgent {
public:
    void SetGoal(WorldState &goalState) {
        goalState.locationA = CLEAN;
        goalState.locationB = CLEAN;
    }

    bool GoalAchieved(const WorldState &state, const WorldState &goalState) {
        return (state.locationA == goalState.locationA && state.locationB == goalState.locationB);
    }

    int CalculateUtility(const WorldState &state) {
        int utility = 0;
        if (state.locationA == CLEAN) utility += 1;
        if (state.locationB == CLEAN) utility += 1;
        return utility;
    }

    void Act(WorldState &state, const WorldState &goalState) {
        WorldState newStateA = state;
        WorldState newStateB = state;
        int utilityCurrent = CalculateUtility(state);
        int utilityActionA = utilityCurrent;
        int utilityActionB = utilityCurrent;

        state.locationA = (rand() % 2 == 0) ? CLEAN : DIRTY;
        state.locationB = (rand() % 2 == 0) ? CLEAN : DIRTY;

        if (state.agentLocation == 'A') {
            if (state.locationA == DIRTY) {
                newStateA.locationA = CLEAN;
                utilityActionA = CalculateUtility(newStateA);
            }
        }

        newStateB.agentLocation = 'B';
        if (state.locationB == DIRTY) {
            newStateB.locationB = CLEAN;
            utilityActionB = CalculateUtility(newStateB);
        }

        if (utilityActionA > utilityCurrent) {
            cout << "A is Dirty, Cleaning A." << endl;
            state.locationA = CLEAN;
        } else if (utilityActionB > utilityCurrent) {
            cout << "B is Dirty, Cleaning B." << endl;
            state.agentLocation = 'B';
            state.locationB = CLEAN;
        } else {
            if (state.agentLocation == 'A') {
                cout << "A is Clean, Moving to B." << endl;
                state.agentLocation = 'B';
            } else {
                cout << "B is Clean, Moving to A." << endl;
                state.agentLocation = 'A';
            }
        }

        if (GoalAchieved(state, goalState)) {
            cout << "Goal achieved! Both locations are clean." << endl;
            exit(0);
        }
    }
};

int main() {
    srand(time(0));
    VacuumAgent agent;
    WorldState state = {DIRTY, DIRTY, 'A'};
    WorldState goalState;

    agent.SetGoal(goalState);
    while(true){
        agent.Act(state, goalState);
    }

    return 0;
}
