
#include <bits/stdc++.h>
using namespace std;
#include "leetcode.h"

class Solution {
 public:
  bool checkTree(TreeNode* root) {
    int left = root->left->val, right = root->right->val, total = root->val;
    return total == left + right;
  }
};