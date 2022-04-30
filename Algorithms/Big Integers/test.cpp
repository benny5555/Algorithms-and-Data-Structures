#include <bits/stdc++.h>

#include "bigint.h"
using namespace std;
int main() {
  bigint n = 1;
  for (int i = 1; i <= 20; ++i) {
    n *= i;
  }
  n = 1;
  for (int i = 0; i < 10; ++i) {
    cout << n++ << endl;
  }
  return 0;
}