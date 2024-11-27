#include <bits/stdc++.h>
using namespace std;
using ActionTable = map<vector<string>, string>;

// Function to look up actions in the table based on percepts
string Lookup(const vector<string>& percepts, const ActionTable& table) {
    auto it = table.find(percepts);
    if (it != table.end()) {
        return it->second;
    }
    return "No action found"; // Default action if not found
}


class TableDrivenAgent {
private:
    vector<string> percepts; // Store percepts
    ActionTable table;       // Store the action table

public:
    TableDrivenAgent(const ActionTable& actionTable) : table(actionTable) {}

    string perceive(const string& percept) {
        // Append the new percept to the percepts list
        percepts.push_back(percept);

        // Lookup the action in the table based on percepts
        string action = Lookup(percepts, table);

        return action;
    }
};

int main(){

    //Rules
    ActionTable actionTable = {
        {{"A dirty"}, "Suck"},
        {{"A clean"}, "Right"},
        {{"B dirty"}, "Suck"},
        {{"B clean"}, "Left"},
        {{"A dirty", "A clean"}, "Right"},
        {{"A clean", "B dirty"}, "Suck"},
        {{"A clean", "B clean"}, "Left"},
        {{"A dirty", "B dirty"}, "Suck"},
        {{"B clean", "A clean"}, "Left"},
        {{"B dirty", "A clean"}, "Left"}
    };

    TableDrivenAgent agent(actionTable);

    vector<string> percepts = {"A dirty", "A clean", "B dirty", "B clean"};
    for (const auto& percept : percepts) {
        // Current Input
        string action = agent.perceive(percept);
    }


    vector<int> percepts;

    int Status = rand() % 2;


}