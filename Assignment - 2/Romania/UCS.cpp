#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, string> PIS;

pair<vector<string>, int> uniformCostSearch(unordered_map<string, unordered_map<string, int>>& graph, string start, string goal) {
    
    priority_queue<PIS, vector<PIS>, greater<PIS>> frontier;
    frontier.push({0, start});

    unordered_map<string, int> cost_so_far;
    cost_so_far[start] = 0;

    unordered_map<string, string> came_from;

    set<string> visited;

    while (!frontier.empty()) {
        int current_cost = frontier.top().first;
        string current_node = frontier.top().second;
        frontier.pop();

        if (current_node == goal) {
            break;
        }

        visited.insert(current_node);

        for (const auto& neighbor : graph[current_node]) {
            string next_node = neighbor.first;
            int edge_cost = neighbor.second;
            int new_cost = current_cost + edge_cost;

            if (cost_so_far.find(next_node) == cost_so_far.end() || new_cost < cost_so_far[next_node]) {
                cost_so_far[next_node] = new_cost;
                frontier.push({new_cost, next_node});
                came_from[next_node] = current_node;
            }
        }
    }

    vector<string> path;
    int total_cost = 0;
    if (came_from.find(goal) != came_from.end()) {
        string current = goal;
        while (current != start) {
            path.push_back(current);
            total_cost += graph[came_from[current]][current];
            current = came_from[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    return {path, total_cost};
}

int main() {


    unordered_map<string, unordered_map<string, int>> graph = {
        {"Arad", {{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}}},
        {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
        {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
        {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu", 80}}},
        {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
        {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
        {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
        {"Rimnicu Vilcea", {{"Sibiu", 80}, {"Pitesti", 97}, {"Craiova", 146}}},
        {"Mehadia", {{"Lugoj", 70}, {"Drobeta", 75}}},
        {"Drobeta", {{"Mehadia", 75}, {"Craiova", 120}}},
        {"Pitesti", {{"Rimnicu", 97}, {"Craiova", 138}, {"Bucharest", 101}}},
        {"Craiova", {{"Rimnicu", 146}, {"Pitesti", 138}, {"Drobeta", 120}}},
        {"Bucharest", {{"Fagaras", 211}, {"Pitesti", 101}, {"Giurgiu", 90}, {"Urziceni", 85}}},
        {"Giurgiu", {{"Bucharest", 90}}},
        {"Urziceni", {{"Bucharest", 85}, {"Vaslui", 142}, {"Hirsova", 98}}},
        {"Vaslui", {{"Urziceni", 142}, {"Iasi", 92}}},
        {"Hirsova", {{"Urziceni", 98}, {"Eforie", 86}}},
        {"Iasi", {{"Vaslui", 92}, {"Neamt", 87}}},
        {"Neamt", {{"Iasi", 87}}},
        {"Eforie", {{"Hirsova", 86}}}
    };

    string start_node, goal_node;
    cout << "Enter the start node: ";
    cin >> start_node;
    cout << "Enter the goal node: ";
    cin >> goal_node;

    auto result = uniformCostSearch(graph, start_node, goal_node);

    cout << "Start State: " << start_node << endl;
    cout << "Target State: " << goal_node << endl;
    cout << "Path: ";
    for (const auto& node : result.first) {
        cout << node << " ";
    }
    cout << endl;
    cout << "Total Cost: " << result.second << endl;

    return 0;
}
