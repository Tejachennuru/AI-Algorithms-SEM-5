#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int N = 8;

int calculateConflicts(const std::vector<int>& board) {
    int conflicts = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (board[i] == board[j] || std::abs(board[i] - board[j]) == j - i) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

std::vector<int> generateRandomBoard() {
    std::vector<int> board(N);
    for (int i = 0; i < N; i++) {
        board[i] = rand() % N;
    }
    return board;
}

void printBoard(const std::vector<int>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[j] == i) std::cout << "Q ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<int> hillClimbing() {
    std::vector<int> currentBoard = generateRandomBoard();
    std::cout << "Generating conflicts less board..." << std::endl;
    int currentConflicts = calculateConflicts(currentBoard);

    while (currentConflicts > 0) {
        bool improved = false;
        for (int col = 0; col < N; col++) {
            int originalRow = currentBoard[col];
            for (int row = 0; row < N; row++) {
                if (row != originalRow) {
                    currentBoard[col] = row;
                    int newConflicts = calculateConflicts(currentBoard);
                    if (newConflicts < currentConflicts) {
                        currentConflicts = newConflicts;
                        improved = true;
                        break;
                    }
                }
            }
            if (improved) break;
            currentBoard[col] = originalRow;
        }
        if (!improved) {
            currentBoard = generateRandomBoard();
            currentConflicts = calculateConflicts(currentBoard);
        }
    }
    return currentBoard;
}


int main() {
    srand(time(0));
    std::vector<int> solution = hillClimbing();
    std::cout << "Solution found:\n";
    printBoard(solution);
    return 0;
}