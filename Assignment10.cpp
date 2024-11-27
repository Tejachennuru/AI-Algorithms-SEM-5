#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

const vector<vector<int>> WINNING_LINES = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
};

// Global variable to count explored states
int stateCount = 0;

void printBoard(const vector<char>& board) {
    for (int i = 0; i < 9; i++) {
        cout << board[i];
        if (i % 3 == 2) cout << endl;
        else cout << "|";
    }
    cout << endl;
}

bool isGameOver(const vector<char>& board) {
    for (const auto& line : WINNING_LINES) {
        if (board[line[0]] != EMPTY &&
            board[line[0]] == board[line[1]] &&
            board[line[0]] == board[line[2]]) {
            return true;
        }
    }
    return find(board.begin(), board.end(), EMPTY) == board.end();
}

int evaluate(const vector<char>& board) {
    for (const auto& line : WINNING_LINES) {
        if (board[line[0]] == AI && board[line[1]] == AI && board[line[2]] == AI) {
            return 10;
        }
        if (board[line[0]] == PLAYER && board[line[1]] == PLAYER && board[line[2]] == PLAYER) {
            return -10;
        }
    }
    return 0;
}

int minimax(vector<char>& board, int depth, bool isMaximizing) {
    stateCount++;  // Increment the state count each time minimax is called

    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (find(board.begin(), board.end(), EMPTY) == board.end()) return 0;

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                bestScore = max(bestScore, minimax(board, depth + 1, false));
                board[i] = EMPTY;
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                bestScore = min(bestScore, minimax(board, depth + 1, true));
                board[i] = EMPTY;
            }
        }
        return bestScore;
    }
}

int findBestMove(vector<char>& board) {
    int bestScore = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int moveScore = minimax(board, 0, false);
            board[i] = EMPTY;

            if (moveScore > bestScore) {
                bestScore = moveScore;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int main() {
    vector<char> board(9, EMPTY);
    
    cout << "Tic Tac Toe" << endl;
    cout << "You are X, AI is O" << endl;

    while (!isGameOver(board)) {
        int move;
        do {
            cout << "Enter your move (0-8): ";
            cin >> move;
        } while (move < 0 || move > 8 || board[move] != EMPTY);

        board[move] = PLAYER;
        printBoard(board);

        if (isGameOver(board)) break;

        cout << "AI is thinking..." << endl;
        int aiMove = findBestMove(board);
        board[aiMove] = AI;
        cout << "AI chose position " << aiMove << endl;
        printBoard(board);
    } 

    int finalScore = evaluate(board);
    if (finalScore > 0) {
        cout << "AI wins!" << endl;
    } else if (finalScore < 0) {
        cout << "You win!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

    // Output the number of explored states
    cout << "States explored by AI: " << stateCount << endl;

    return 0;
}
