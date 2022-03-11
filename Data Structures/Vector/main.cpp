#include <iostream>
#include <vector>

#include "vector.h"
using namespace std;

int main() {
  master::vector<int> v{1, 3, 5};
  for (auto iter = v.rbegin(); iter != v.rend(); ++iter) {
    cout << *iter << endl;
  }
  v.resize(1);
  for (auto iter : v) {
    cout << iter << " ";
  }
  cout << endl;
  vector<int> v1{1, 3, 5};
  v1.reserve(5);
  for (int num : v1) {
    cout << num << " ";
  }
  cout << endl;
  cout << v.max_size() << " " << v1.max_size() << endl;
  return 0;
}