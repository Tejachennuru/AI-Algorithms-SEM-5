#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int N = 3;
const vector<vector<int>> GOAL = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

struct State {
    vector<vector<int>> board;
    int depth;
    
    State(vector<vector<int>> b, int d) : board(b), depth(d) {}
};

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int tile : row) {
            cout << tile << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isGoal(const vector<vector<int>>& state) {
    return state == GOAL;
}

vector<State> getNeighbors(const State& current) {
    vector<State> neighbors;
    int x, y;
    
    // Find the empty tile (0) 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (current.board[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }
    
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& dir : directions) {
        int newX = x + dir.first, newY = y + dir.second;
        if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
            vector<vector<int>> newBoard = current.board;
            swap(newBoard[x][y], newBoard[newX][newY]);
            neighbors.emplace_back(newBoard, current.depth + 1);
        }
    }
    return neighbors;
}

struct VectorHash {
    size_t operator()(const vector<vector<int>>& board) const {
        size_t hash = 0;
        for (const auto& row : board) {
            for (int tile : row) {
                hash = hash * 31 + tile;
            }
        }
        return hash;
    }
};

void solve(const vector<vector<int>>& start) {
    queue<State> openSet;
    unordered_set<vector<vector<int>>, VectorHash> closedSet;
    
    openSet.push(State(start, 0));
    
    while (!openSet.empty()) {
        State current = openSet.front();
        openSet.pop();
        
        if (isGoal(current.board)) {
            cout << "Goal reached with depth: " << current.depth << "\n";
            printBoard(current.board);
            return;
        }

        closedSet.insert(current.board);

        vector<State> neighbors = getNeighbors(current);
        for (const auto& neighbor : neighbors) {
            if (closedSet.find(neighbor.board) == closedSet.end()) {
                openSet.push(neighbor);
            }
        }
    }
    
    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {4, 0, 6}, {7, 5, 8}};
    
    cout << "Enter the Initial State" << endl;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> start[i][j];
        }
    }
    solve(start);
    return 0;
}
