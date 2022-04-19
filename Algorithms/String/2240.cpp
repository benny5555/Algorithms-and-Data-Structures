#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  long long waysToBuyPensPencils(int total, int cost1, int cost2) {
    long long ans = 0;
    int cnt1 = total / cost1;
    for (int i = 0; i <= cnt1; ++i) {
      ans += max(1, (total - i * cost1) / cost2 + 1);
    }
    return ans;
  }
};