#include<bits/stdc++.h>
using namespace std;
 
int main() {
  srand(time(0));
  int n;
  int num;
  n = rand() % 100+1;
  cout << "Guess a number between 1 and 100: " << endl;
  int low = 1;
  int high = 100;
  int count = 0;
  while(true){
    cin >> num;
    count++;
    cout << "Random number is "<< n << endl;
    if(num == n){
        cout << "You win!" << endl;
        cout << "Attempts: " << count;
        return 0;
    }
    else if(num < n){
        cout << "Too small!" << endl;
        low = num + 1;
    }
    else if(num > n){
        cout << "Too big!" << endl;
        high = num - 1;
    }
    if (low <= high) {
        n = low + rand() % (high - low + 1);
    }
  }
  return 0;
}