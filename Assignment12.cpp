#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';

const vector<vector<int>> WINNING_LINES = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
    {0, 4, 8}, {2, 4, 6}             // Diagonals 
};

void print_board(const vector<char>& board) {
    for (int i = 0; i < 9; i += 3) {
        cout << board[i] << " | " << board[i+1] << " | " << board[i+2] << "\n";
        if (i < 6) cout << "--+---+--\n";
    }
}

bool is_winner(const vector<char>& board, char player) {
    for (const auto& line : WINNING_LINES) {
        if (board[line[0]] == player && board[line[1]] == player && board[line[2]] == player) {
            return true;
        }
    }
    return false;
}

bool is_board_full(const vector<char>& board) {
    for (char cell : board) {
        if (cell == EMPTY) return false;
    }
    return true;
}

vector<int> get_available_moves(const vector<char>& board) {
    vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == EMPTY) moves.push_back(i);
    }
    return moves;
}

int evaluate(const vector<char>& board) {
    if (is_winner(board, PLAYER_X)) return 10;
    else if (is_winner(board, PLAYER_O)) return -10;
    return 0;
}

int minimax(vector<char>& board, int depth, bool is_maximizing, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (is_board_full(board)) return 0;

    if (is_maximizing) {
        int best_score = -numeric_limits<int>::max();
        for (int move : get_available_moves(board)) {
            board[move] = PLAYER_X;
            best_score = max(best_score, minimax(board, depth + 1, false, alpha, beta));
            board[move] = EMPTY;
            alpha = max(alpha, best_score);
            if (beta <= alpha) break; // Beta cut-off
        }
        return best_score;
    } else {
        int best_score = numeric_limits<int>::max();
        for (int move : get_available_moves(board)) {
            board[move] = PLAYER_O;
            best_score = min(best_score, minimax(board, depth + 1, true, alpha, beta));
            board[move] = EMPTY;
            beta = min(beta, best_score);
            if (beta <= alpha) break; // Alpha cut-off
        }
        return best_score;
    }
}

int find_best_move(vector<char>& board, char player) {
    int best_move = -1;
    int best_score = (player == PLAYER_X) ? -numeric_limits<int>::max() : numeric_limits<int>::max();

    for (int move : get_available_moves(board)) {
        board[move] = player;
        int move_score = minimax(board, 0, player == PLAYER_O, -numeric_limits<int>::max(), numeric_limits<int>::max());
        board[move] = EMPTY;

        if ((player == PLAYER_X && move_score > best_score) || (player == PLAYER_O && move_score < best_score)) {
            best_score = move_score;
            best_move = move;
        }
    }

    return best_move;
}

void play_game() {
    vector<char> board(9, EMPTY);
    char current_player = PLAYER_X;
    cout << "You are O, AI is X.\n";

    while (true) {
        print_board(board);

        if (is_winner(board, PLAYER_X)) {
            cout << "Player X (AI) wins!\n";
            break;
        } else if (is_winner(board, PLAYER_O)) {
            cout << "Player O (You) wins!\n";
            break;
        } else if (is_board_full(board)) {
            cout << "It's a draw!\n";
            break;
        }

        int move;
        if (current_player == PLAYER_X) {
            cout << "Player X's turn (AI):\n";
            move = find_best_move(board, PLAYER_X);
        } else {
            cout << "Your turn (O), enter the move (0-8): ";
            cin >> move;
            while (board[move] != EMPTY || move < 0 || move > 8) {
                cout << "Invalid move. Enter an empty cell (0-8): ";
                cin >> move;
            }
        }

        board[move] = current_player;
        current_player = (current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
}

int main() {
    play_game();
    return 0;
}
