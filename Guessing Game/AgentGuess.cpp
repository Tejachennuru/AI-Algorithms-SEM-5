#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter a number between 1 and 100: " << endl;
    cin >> n;

    int low = 1;
    int high = 100;
    int attempts = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        attempts++;

        if (mid == n) {
            cout << "The computer guessed the number " << n << " in " << attempts << " attempts!" << endl;
            break;
        } else if (mid < n) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}
