#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

tuple<char, char, char, char> initial_state = make_tuple('L', 'L', 'L', 'L');
tuple<char, char, char, char> goal_state = make_tuple('R', 'R', 'R', 'R');

bool is_valid(const tuple<char, char, char, char>& state) {
    char M, T, G, C;
    tie(M, T, G, C) = state;
 
    if ((T == G && M != T) || (G == C && M != G)) {
        return false;
    }
    return true;
}

vector<tuple<char, char, char, char>> get_next_states(const tuple<char, char, char, char>& state) {
    char M, T, G, C;
    tie(M, T, G, C) = state;
    vector<tuple<char, char, char, char>> next_states;
    

    if (M == 'L') {
        next_states.push_back(make_tuple('R', T, G, C));
    } else {
        next_states.push_back(make_tuple('L', T, G, C));
    }
 
    if (M == T) {
        if (M == 'L') {
            next_states.push_back(make_tuple('R', 'R', G, C));
        } else {
            next_states.push_back(make_tuple('L', 'L', G, C));
        }
    }
    
    if (M == G) {
        if (M == 'L') {
            next_states.push_back(make_tuple('R', T, 'R', C));
        } else {
            next_states.push_back(make_tuple('L', T, 'L', C));
        }
    }
    
    if (M == C) {
        if (M == 'L') {
            next_states.push_back(make_tuple('R', T, G, 'R'));
        } else {
            next_states.push_back(make_tuple('L', T, G, 'L'));
        }
    }
    
    vector<tuple<char, char, char, char>> valid_states;
    for (const auto& s : next_states) {
        if (is_valid(s)) {
            valid_states.push_back(s);
        }
    }
    
    return valid_states;
}

vector<tuple<char, char, char, char>> solve_puzzle() {
    queue<pair<tuple<char, char, char, char>, vector<tuple<char, char, char, char>>>> q;
    set<tuple<char, char, char, char>> visited;

    q.push(make_pair(initial_state, vector<tuple<char, char, char, char>>()));

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        tuple<char, char, char, char> current_state = current.first;
        vector<tuple<char, char, char, char>> path = current.second;

        if (visited.find(current_state) != visited.end()) {
            continue;
        }

        visited.insert(current_state);
        path.push_back(current_state);

        if (current_state == goal_state) {
            return path;
        }

        vector<tuple<char, char, char, char>> next_states = get_next_states(current_state);

        for (const auto& next_state : next_states) {
            if (visited.find(next_state) == visited.end()) {
                q.push(make_pair(next_state, path));
            }
        }
    }

    return vector<tuple<char, char, char, char>>(); 
}

void print_solution(const vector<tuple<char, char, char, char>>& solution) {
    if (!solution.empty()) {
        cout << "Solution found:" << endl;
        cout << "Man Tiger Goat Cabbage " << endl;
        for (const auto& step : solution) {
            char M, T, G, C;
            tie(M, T, G, C) = step;
            cout << "(" << M << ", " << T << ", " << G << ", " << C << ")" << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }
}

int main() {
    vector<tuple<char, char, char, char>> solution = solve_puzzle();
    print_solution(solution);

    return 0;
}
