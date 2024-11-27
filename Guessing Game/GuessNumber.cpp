#include<bits/stdc++.h>
using namespace std;
 
int main() {
  int n;
  int num;
  n = rand() % 100;
  cout << "Guess a number between 1 and 100: " << endl;
  while(true){
    cin >> num;
    if(num == n){
        cout << "You win!" << endl;
        return 0;
    }
    else if(num < n){
        cout << "Too small!" << endl;
    }
    else if(num > n){
        cout << "Too big!" << endl;
    }
  }
  return 0;
}