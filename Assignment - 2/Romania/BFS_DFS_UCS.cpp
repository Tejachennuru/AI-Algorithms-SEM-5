#include <bits/stdc++.h>

using namespace std;

int bfs_expored_count = 0;
int dfs_expored_count = 0;
int ucs_expored_count = 0;
int astar_expored_count = 0;
int befs_expored_count = 0;
int rbfs_expored_count = 0;

typedef pair<int, string> PIS;

pair<vector<string>, int> uniformCostSearch(unordered_map<string, unordered_map<string, int>>& graph, string start, string goal) {
    priority_queue<PIS, vector<PIS>, greater<PIS>> frontier;
    frontier.push({0, start});

    unordered_map<string, int> cost_so_far;
    cost_so_far[start] = 0;

    unordered_map<string, string> came_from;

    while (!frontier.empty()) {
        int current_cost = frontier.top().first;
        string current_node = frontier.top().second;
        frontier.pop();

        
        cout << "Exploring node: " << current_node << " with cost: " << current_cost << endl;
        ucs_expored_count++;

        if (current_node == goal) {
            break;
        }

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

pair<vector<string>, int> breadthFirstSearch(unordered_map<string, unordered_map<string, int>>& graph, string start, string goal) {
    queue<string> frontier;
    frontier.push(start);

    unordered_map<string, string> came_from;
    came_from[start] = "";

    while (!frontier.empty()) {
        string current_node = frontier.front();
        frontier.pop();

        cout << "Exploring node: " << current_node << endl;
        bfs_expored_count++;

        if (current_node == goal) {
            break;
        }

        for (const auto& neighbor : graph[current_node]) {
            string next_node = neighbor.first;
            if (came_from.find(next_node) == came_from.end()) {
                frontier.push(next_node);
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

pair<vector<string>, int> depthFirstSearch(unordered_map<string, unordered_map<string, int>>& graph, string start, string goal) {
    stack<string> frontier;
    frontier.push(start);

    unordered_map<string, string> came_from;
    came_from[start] = "";

    while (!frontier.empty()) {
        string current_node = frontier.top();
        frontier.pop();

        cout << "Exploring node: " << current_node << endl;
        dfs_expored_count++;
        
        if (current_node == goal) {
            break;
        }

        for (const auto& neighbor : graph[current_node]) {
            string next_node = neighbor.first;
            if (came_from.find(next_node) == came_from.end()) {
                frontier.push(next_node);
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

pair<vector<string>, int> aStarSearch(unordered_map<string, unordered_map<string, int>>& graph, unordered_map<string, int>& heuristics, string start, string goal) {
    priority_queue<PIS, vector<PIS>, greater<PIS>> frontier;
    frontier.push({heuristics[start], start});

    unordered_map<string, int> cost_so_far;
    cost_so_far[start] = 0;

    unordered_map<string, string> came_from;

    while (!frontier.empty()) {
        int current_cost = frontier.top().first - heuristics[frontier.top().second];
        string current_node = frontier.top().second;
        frontier.pop();

        cout << "Exploring node: " << current_node << " with cost: " << current_cost << endl;
        astar_expored_count++;

        if (current_node == goal) {
            break;
        }

        for (const auto& neighbor : graph[current_node]) {
            string next_node = neighbor.first;
            int edge_cost = neighbor.second;
            int new_cost = current_cost + edge_cost;

            if (cost_so_far.find(next_node) == cost_so_far.end() || new_cost < cost_so_far[next_node]) {
                cost_so_far[next_node] = new_cost;
                int priority = new_cost + heuristics[next_node];
                frontier.push({priority, next_node});
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

pair<vector<string>, int> bestFirstSearch(unordered_map<string, unordered_map<string, int>>& graph, unordered_map<string, int>& heuristics, string start, string goal) {
    priority_queue<PIS, vector<PIS>, greater<PIS>> frontier;
    frontier.push({heuristics[start], start});

    unordered_map<string, string> came_from;

    while (!frontier.empty()) {
        string current_node = frontier.top().second;
        frontier.pop();

        cout << "Exploring node: " << current_node << endl;
        befs_expored_count++;

        if (current_node == goal) {
            break;
        }

        for (const auto& neighbor : graph[current_node]) {
            string next_node = neighbor.first;
            if (came_from.find(next_node) == came_from.end()) {
                frontier.push({heuristics[next_node], next_node});
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
            cout << total_cost << endl;
            current = came_from[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    return {path, total_cost};
}

pair<vector<string>, int> RBFS(unordered_map<string, unordered_map<string, int>>& graph, unordered_map<string, int>& heuristics, string current_node, string goal, int f_limit, unordered_map<string, string>& came_from) {
    if (current_node == goal) {
        vector<string> path;
        int total_cost = 0;
        string current = goal;
        while (current != came_from[current]) {
            path.push_back(current);
            total_cost += graph[came_from[current]][current];
            current = came_from[current];
        }
        path.push_back(current);
        reverse(path.begin(), path.end());
        return {path, total_cost};
    }

    vector<PIS> successors;
    for (const auto& neighbor : graph[current_node]) {
        int f_value = heuristics[neighbor.first];
        successors.push_back({f_value, neighbor.first});
    }

    if (successors.empty()) {
        return {vector<string>(), numeric_limits<int>::max()};
    }

    sort(successors.begin(), successors.end());

    while (true) {
        PIS best = successors[0];
        if (best.first > f_limit) {
            return {vector<string>(), best.first};
        }

        int alternative = successors.size() > 1 ? successors[1].first : numeric_limits<int>::max();

        came_from[best.second] = current_node;
        rbfs_expored_count++;

        pair<vector<string>, int> result = RBFS(graph, heuristics, best.second, goal, min(f_limit, alternative), came_from);
        if (!result.first.empty()) {
            return result;
        }

        successors[0].first = result.second;
        sort(successors.begin(), successors.end());
    }
}

pair<vector<string>, int> recursiveBestFirstSearch(unordered_map<string, unordered_map<string, int>>& graph, unordered_map<string, int>& heuristics, string start, string goal) {
    unordered_map<string, string> came_from;
    came_from[start] = start;
    return RBFS(graph, heuristics, start, goal, numeric_limits<int>::max(), came_from);
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
        {"Rimnicu", {{"Sibiu", 80}, {"Pitesti", 97}, {"Craiova", 146}}},
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
/*

    unordered_map<string, unordered_map<string, int>> graph = {
    {"Bangalore", {{"Mysore", 150}, {"Chennai", 350}, {"Hyderabad", 570}, {"Coimbatore", 363}}},
    {"Mysore", {{"Bangalore", 150}, {"Coimbatore", 204}, {"Ooty", 125}}},
    {"Chennai", {{"Bangalore", 350}, {"Pondicherry", 150}, {"Coimbatore", 510}, {"Madurai", 460}}},
    {"Coimbatore", {{"Bangalore", 363}, {"Mysore", 204}, {"Chennai", 510}, {"Madurai", 210}, {"Ooty", 85}}},
    {"Hyderabad", {{"Bangalore", 570}, {"Chennai", 627}, {"Vijayawada", 275}, {"Tirupati", 550}}},
    {"Ooty", {{"Mysore", 125}, {"Coimbatore", 85}}},
    {"Madurai", {{"Chennai", 460}, {"Coimbatore", 210}, {"Trichy", 130}, {"Tirunelveli", 160}}},
    {"Pondicherry", {{"Chennai", 150}, {"Trichy", 200}}},
    {"Trichy", {{"Madurai", 130}, {"Pondicherry", 200}, {"Tiruchendur", 145}}},
    {"Tiruchendur", {{"Trichy", 145}, {"Madurai", 160}, {"Tirunelveli", 60}}},
    {"Tirunelveli", {{"Madurai", 160}, {"Tiruchendur", 60}, {"Kanyakumari", 90}}},
    {"Kanyakumari", {{"Tirunelveli", 90}, {"Madurai", 250}}},
    {"Vijayawada", {{"Hyderabad", 275}, {"Tirupati", 380}, {"Visakhapatnam", 350}}},
    {"Tirupati", {{"Hyderabad", 550}, {"Vijayawada", 380}, {"Chennai", 135}}},
    {"Visakhapatnam", {{"Vijayawada", 350}, {"Hyderabad", 620}}}
};

*/

    unordered_map<string, int> Arad_Bucharest_Heuristics = {
        {"Arad", 366},
        {"Zerind", 374},
        {"Timisoara", 329},
        {"Sibiu", 253},
        {"Oradea", 380},
        {"Lug/0oj", 244},
        {"Fagaras", 176},
        {"Rimnicu", 193},
        {"Mehadia", 241},
        {"Drobeta", 242},
        {"Pitesti", 100},
        {"Craiova", 160},
        {"Bucharest", 0},
        {"Giurgiu", 77},
        {"Urziceni", 80},
        {"Vaslui", 199},
        {"Hirsova", 151},
        {"Iasi", 226},
        {"Neamt", 234},
        {"Eforie", 161}
    };

    string start_node, goal_node;
    cout << "Enter the start node: ";
    cin >> start_node;
    cout << "Enter the goal node: ";
    cin >> goal_node;

    int choice;
    cout << "Select search algorithm:\n1. Uniform Cost Search (UCS)\n2. Breadth-First Search (BFS)\n3. Depth-First Search (DFS)\n4. A* Search\n5. Best-First Search (BeFS)\n6. Recursive Best-First Search (RBFS)\n";
    cin >> choice;

    pair<vector<string>, int> result;

    switch (choice) {
        case 1:
            result = uniformCostSearch(graph, start_node, goal_node);
            cout << "Count: " << ucs_expored_count << endl;
            cout << "Uniform Cost Search (UCS) - Path: ";
            break;
        case 2:
            result = breadthFirstSearch(graph, start_node, goal_node);
            cout << "Count: " << bfs_expored_count << endl;
            cout << "Breadth-First Search (BFS) - Path: ";
            break;
        case 3:
            result = depthFirstSearch(graph, start_node, goal_node);
            cout << "Count: " << dfs_expored_count << endl;
            cout << "Depth-First Search (DFS) - Path: ";
            break;
        case 4:
            result = aStarSearch(graph, Arad_Bucharest_Heuristics, start_node, goal_node);
            cout << "Count: " << astar_expored_count << endl;
            cout << "A* Search - Path: ";
            break;
        case 5:
            result = bestFirstSearch(graph, Arad_Bucharest_Heuristics, start_node, goal_node);
            cout << "Count: " << befs_expored_count << endl;
            cout << "Best-First Search (BeFS) - Path: ";
            break;
        case 6:
            result = recursiveBestFirstSearch(graph, Arad_Bucharest_Heuristics, start_node, goal_node);
            cout << "Count: " << rbfs_expored_count << endl;
            cout << "Recursive Best-First Search (RBFS) - Path: ";
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    for (const auto& node : result.first) {
        cout << node << " ";
    }
    cout << endl << "Total Cost: " << result.second << endl;

    return 0;
}
