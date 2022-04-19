#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  int findClosestNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end(), [&](auto& a, auto& b) {
      if (abs(a) == abs(b)) return a < b;
      return abs(a) < abs(b);
    });
    int ind = 0, initial = abs(nums[0]);
    while (ind < nums.size() && abs(nums[ind]) == initial) ++ind;
    return nums[ind - 1];
  }
};