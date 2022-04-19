#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  int meetRequirement(int n, vector<vector<int>>& lights,
                      vector<int>& requirement) {
    vector<int> ans(n + 1);
    for (auto& light : lights) {
      ++ans[max(0, light[0] - light[1])];
      --ans[min(n, light[0] + light[1] + 1)];
    }
    int bright = 0, res = 0;
    for (int i = 0; i < n; ++i) {
      bright += ans[i];
      if (bright >= requirement[i]) ++res;
    }
    return res;
  }
};