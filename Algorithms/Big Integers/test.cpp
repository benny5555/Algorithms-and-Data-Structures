#include <bits/stdc++.h>

#include "bigint.h"
using namespace std;
int main() {
  bigint n = 1;
  for (int i = 1; i <= 20; ++i) {
    n *= i;
  }
  n = 20;
  return 0;
}