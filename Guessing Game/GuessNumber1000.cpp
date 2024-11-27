#include<bits/stdc++.h>
using namespace std;
 
int main() {
  int n;
  int num;
  n = rand() % 1000;
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