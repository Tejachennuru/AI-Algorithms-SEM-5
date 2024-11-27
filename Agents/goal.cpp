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
    void SetGoal(WorldState &goalState) {
        goalState.locationA = CLEAN;
        goalState.locationB = CLEAN;
    }

    bool GoalAchieved(const WorldState &state, const WorldState &goalState) {
        return (state.locationA == goalState.locationA && state.locationB == goalState.locationB);
    }

    void Act(WorldState &state, const WorldState &goalState) {
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

        // Check if the goal is achieved after each action
        if (GoalAchieved(state, goalState)) {
            cout << "Goal achieved! Both locations are clean." << endl;
            exit(0);
        }
    }
};

int main() {
    VacuumAgent agent;
    WorldState state = {DIRTY, DIRTY, 'A'};
    WorldState goalState;

    agent.SetGoal(goalState);
    while(true){
        agent.Act(state, goalState);
    }

    return 0;
}
