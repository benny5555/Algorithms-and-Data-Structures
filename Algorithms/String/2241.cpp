#include <bits/stdc++.h>
using namespace std;
class ATM {
 private:
  vector<long long> cnt;

 public:
  ATM() : cnt(5) {}

  void deposit(vector<int> banknotesCount) {
    for (int i = 0; i < banknotesCount.size(); ++i) {
      cnt[i] += banknotesCount[i];
    }
  }

  vector<int> withdraw(long long amount) {
    vector<int> ans(5);
    for (int i = 4; i > -1; --i) {
      if (i == 4 && amount >= 500) {
        int num = min(amount / 500, cnt[i]);
        ans[i] += num;
        amount -= 500 * num;
      } else if (i == 3 && amount >= 200) {
        int num = min(amount / 200, cnt[i]);
        ans[i] += num;
        amount -= 200 * num;
      } else if (i == 2 && amount >= 100) {
        int num = min(amount / 100, cnt[i]);
        ans[i] += num;
        amount -= 100 * num;
      } else if (i == 1 && amount >= 50) {
        int num = min(amount / 50, cnt[i]);
        ans[i] += num;
        amount -= 50 * num;
      } else if (i == 0 && amount >= 20) {
        int num = min(amount / 20, cnt[i]);
        ans[i] += num;
        amount -= 20 * num;
      }
    }
    if (amount == 0) {
      for (int i = 0; i < 5; ++i) {
        cnt[i] -= ans[i];
      }
      return ans;
    } else
      return {-1};
  }
};