#include <bits/stdc++.h>
using namespace std;
#define N 3

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

struct Node {
    Node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

int printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return 0;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->x = newX;
    node->y = newY;
    node->level = level;
    return node;
}

int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root) {
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    printf("\n");
}


int manhattanDistance(int initial[N][N], int final[N][N]) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] != 0) {
                int targetX = (initial[i][j] - 1) / N;
                int targetY = (initial[i][j] - 1) % N;
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return distance;
}


int linearConflict(int initial[N][N], int final[N][N]) {
    int linearConflictCount = 0;


    for (int row = 0; row < N; row++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (initial[row][i] && initial[row][j] &&
                    (initial[row][i] - 1) / N == row && (initial[row][j] - 1) / N == row &&
                    initial[row][i] > initial[row][j]) {
                    linearConflictCount += 2;  // Two moves needed to resolve the conflict
                }
            }
        }
    }

    // Column-wise conflict
    for (int col = 0; col < N; col++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (initial[i][col] && initial[j][col] &&
                    (initial[i][col] - 1) % N == col && (initial[j][col] - 1) % N == col &&
                    initial[i][col] > initial[j][col]) {
                    linearConflictCount += 2;  // Two moves needed to resolve the conflict
                }
            }
        }
    }

    return linearConflictCount;
}

// Combined Heuristic (Manhattan + Linear Conflict)
int calculateHeuristic(int initial[N][N], int final[N][N]) {
    int manhattan = manhattanDistance(initial, final);
    int conflict = linearConflict(initial, final);
    return manhattan + conflict;
}

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

void aStarSearch(int initial[N][N], int x, int y, int final[N][N]) {
    priority_queue<Node*, vector<Node*>, comp> pq;

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateHeuristic(initial, final); 

    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        if (memcmp(min->mat, final, sizeof(min->mat)) == 0) {
            printPath(min);
            cout << "You Reached the Goal" << endl;
            cout << "No of States: " << min->level << endl;
            return;
        }
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateHeuristic(child->mat, final);  // Heuristic for the child
                pq.push(child);
            }
        }
    }
}

int main() {
    int x, y;
    int initial[N][N];
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

    int final[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    if (inversions % 2 != 0) {
        cout << "Not Possible!" << endl;
    } else {
        aStarSearch(initial, x, y, final);
    }

    return 0;
}
