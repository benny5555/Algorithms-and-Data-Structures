#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
    int n = scores.size();
    vector<vector<int>> graph(n);
    for (auto& e : edges) {
      graph[e[0]].push_back(e[1]);
      graph[e[1]].push_back(e[0]);
    }

    for (auto& v : graph) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
      for (int next : v) {
        int score = scores[next];
        if (pq.size() < 3 || pq.top().first < score) {
          pq.push({score, next});
          if (pq.size() > 3) pq.pop();
        }
      }
      v.resize(pq.size());
      for (int i = v.size() - 1; i > -1; --i) {
        v[i] = pq.top().second;
        pq.pop();
      }
    }
    int ans = -1;
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      for (auto nextu : graph[u]) {
        if (nextu == v) continue;
        for (auto nextv : graph[v]) {
          if (nextv == u || nextu == nextv) continue;
          ans = max(ans, scores[u] + scores[v] + scores[nextu] + scores[nextv]);
        }
      }
    }
    return ans;
  }
};