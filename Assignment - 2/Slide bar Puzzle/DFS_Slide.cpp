#include <bits/stdc++.h>
using namespace std;
#define N 3

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
    int level;
};

int printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent)
{
    Node* node = new Node;

    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);

    node->level = level;
    node->x = newX;
    node->y = newY;

    return node;
}

bool isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    printf("\n");
}

void solveDFS(int initial[N][N], int x, int y, int final[N][N])
{
    stack<Node*> s;
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    s.push(root);

    while (!s.empty())
    {
        Node* min = s.top();
        s.pop();

        if (memcmp(min->mat, final, sizeof min->mat) == 0)
        {
            printPath(min);
            cout << "You Reached the Goal" << endl;
            cout << "No of States: " << min->level << endl;
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                s.push(child);
            }
        }
    }
}

int main()
{
    int x, y;
    int initial[N][N];
    int inversions = 0;

    cout << "Enter the Initial State" << endl;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> initial[i][j];
            if(initial[i][j] == 0){
                x = i;
                y = j;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                for(int l = 0; l < N; l++) {
                    if((i < k) || (i == k && j < l)) {
                        if(initial[i][j] > initial[k][l] && initial[k][l] != 0) {
                            inversions++;
                        }
                    }
                }
            }
        }
    }

    int final[N][N] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    
    if(inversions % 2 != 0){
        cout << "Not Possible!";
    }
    else{
        solveDFS(initial, x, y, final);
    }

    return 0;
}
