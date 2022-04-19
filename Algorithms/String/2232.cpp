#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  string minimizeResult(string expression) {
    int ind = expression.find("+");
    string num1 = expression.substr(0, ind), num2 = expression.substr(ind + 1);
    int mmin = INT_MAX;
    string ans;
    for (int b1 = 0; b1 < num1.size(); ++b1) {
      for (int b2 = b1; b2 < num2.size(); ++b2) {
        string left_out = num1.substr(0, b1), right_out = num2.substr(b2 + 1);
        int left_num = 1, right_num = 1;
        if (left_out.empty())
          left_num = 1;
        else
          left_num = stoi(num1.substr(0, b1));
        if (right_out.empty())
          right_num = 1;
        else
          right_num = stoi(num2.substr(b2 + 1));
        int mid = stoi(num1.substr(b1)) + stoi(num2.substr(0, b2 + 1));
        int temp = mid * left_num * right_num;
        if (temp < mmin) {
          mmin = temp;
          ans = left_out + "(" + num1.substr(b1) + "+" +
                num2.substr(0, b2 + 1) + ")" + right_out;
        }
      }
    }
    return ans;
  }
};