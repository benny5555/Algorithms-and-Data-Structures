#include <bits/stdc++.h>

#include "bigint.h"
using namespace std;
int main() {
  bigint n = 1;
  for (int i = 1; i <= 20; ++i) {
    n *= i;
  }
  n = 101;
  cout << n % 50 << endl;
  return 0;
}