#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    int num;
    int limit = 6;
    int choice;

    do {
        n = rand() % 100 ;
        cout << "Guess a number between 1 and 100: " << endl;
        cout << "You have 6 attempts" << endl;

        for (int attempts = 0; attempts < limit; ++attempts) {
            cin >> num;

            if (num == n) {
                cout << "You win!" << endl;
                break;
            } else if (num < n) {
                cout << "Too small!" << endl;
            } else {
                cout << "Too big!" << endl;
            }

            if (attempts == limit - 1) {
                cout << "You Lose!" << endl;
            }
        }

        cout << "1. Continue" << endl;
        cout << "2. EXIT" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice == 1);

    return 0;
}
