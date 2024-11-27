#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;

const int N = 3;

struct State {
    vector<vector<int>> board;
    int g, h, f;
    pair<int, int> blank;
    vector<State*> path;

    State(vector<vector<int>> b, int g, int h, pair<int, int> blank, vector<State*> path)
        : board(b), g(g), h(h), f(g + h), blank(blank), path(path) {}

    bool operator<(const State& other) const {
        return f > other.f;
    }
};

int calculateMisplacedTiles(const vector<vector<int>>& board, const vector<vector<int>>& goal) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0 && board[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

int calculateManhattanDistance(const vector<vector<int>>& board, const vector<vector<int>>& goal) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {
                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        if (board[i][j] == goal[x][y]) {
                            distance += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return distance;
}

vector<State*> getNeighbors(State* current) {
    vector<State*> neighbors;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = current->blank.first + dx[i];
        int ny = current->blank.second + dy[i];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            vector<vector<int>> newBoard = current->board;
            swap(newBoard[current->blank.first][current->blank.second], newBoard[nx][ny]);

            vector<State*> newPath = current->path;
            newPath.push_back(current);

            neighbors.push_back(new State(newBoard, current->g + 1, 0, make_pair(nx, ny), newPath));
        }
    }

    return neighbors;
}

string boardToString(const vector<vector<int>>& board) {
    string result;
    for (const auto& row : board) {
        for (int val : row) {
            result += to_string(val);
        }
    }
    return result;
}

vector<State*> solvePuzzle(const vector<vector<int>>& initial, const vector<vector<int>>& goal, bool useManhattan) {
    auto cmp = [](State* a, State* b) { return a->f > b->f; };
    priority_queue<State*, vector<State*>, decltype(cmp)> openList(cmp);

    unordered_set<string> closedList;

    pair<int, int> initialBlank;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] == 0) {
                initialBlank = make_pair(i, j);
                break;
            }
        }
    }

    State* start = new State(initial, 0, 0, initialBlank, {});
    start->h = useManhattan ? calculateManhattanDistance(initial, goal) : calculateMisplacedTiles(initial, goal);
    openList.push(start);

    while (!openList.empty()) {
        State* current = openList.top();
        openList.pop();

        if (current->board == goal) {
            return current->path;
        }

        string boardStr = boardToString(current->board);
        if (closedList.find(boardStr) != closedList.end()) {
            continue;
        }
        closedList.insert(boardStr);

        for (State* neighbor : getNeighbors(current)) {
            neighbor->h = useManhattan ? calculateManhattanDistance(neighbor->board, goal) : calculateMisplacedTiles(neighbor->board, goal);
            openList.push(neighbor);
        }
    }

    return {};
}

int main() {
    int x, y;
    vector<vector<int>> initial(N, vector<int>(N));
    int inversions = 0;

    cout << "Enter the Initial State" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initial[i][j];
            if (initial[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    if ((i < k) || (i == k && j < l)) {
                        if (initial[i][j] > initial[k][l] && initial[k][l] != 0) {
                            inversions++;
                        }
                    }
                }
            }
        }
    }

    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    if (inversions % 2 != 0) {
        cout << "Not Possible!" << endl;
    } else {
        cout << "Solving with Misplaced Tiles heuristic..." << endl;
        auto start = chrono::high_resolution_clock::now();
        vector<State*> solutionMisplaced = solvePuzzle(initial, goal, false);
        auto end = chrono::high_resolution_clock::now();
        auto durationMisplaced = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "Misplaced Tiles:" << endl;
        cout << "Time taken: " << durationMisplaced.count() << " milliseconds" << endl;
        cout << "Number of moves: " << solutionMisplaced.size() << endl;

        cout << "Solving with Manhattan Distance heuristic..." << endl;
        start = chrono::high_resolution_clock::now();
        vector<State*> solutionManhattan = solvePuzzle(initial, goal, true);
        end = chrono::high_resolution_clock::now();
        auto durationManhattan = chrono::duration_cast<chrono::milliseconds>(end - start);


        cout << "\nManhattan Distance:" << endl;
        cout << "Time taken: " << durationManhattan.count() << " milliseconds" << endl;
        cout << "Number of moves: " << solutionManhattan.size() << endl;
    }

    return 0;
}