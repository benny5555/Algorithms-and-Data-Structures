# Prefix Function
## Definition
You are given a string s of length n. The prefix function for this string is defined as an array $\pi$ of length n, where $\pi[i]$ is the length of the longest proper prefix of the substring $s[0...i]$ which is also a suffix of this substring. A proper prefix of a string is a prefix that is not equal to the string itself. By definition, $\pi[0]=0$.

For example, to the string "abcabcd"

$\pi = [0, 0, 0, 1, 2, 3, 0]$

## Brute Force
```C++
// C++ Version
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++)
    for (int j = i; j >= 0; j--)
      if (s.substr(0, j) == s.substr(i - j + 1, j)) {
        pi[i] = j;
        break;
      }
  return pi;
}
```

## Optimized version
```C++
vector<int> prefix_function(const string &s) {
  vector<int> pi(s.size());
  for (int i = 1; i < s.size(); ++i) {
    int j = pi[i - 1];
    while (j && s[i] != s[j]) j = pi[j];
    j += s[i] == s[j];
    pi[i] = j;
  }
  return pi;
}
```

# Z Algorithm
## Definition
Given a string s with n length, $z[i]$ represents $s$ and $s[i, n - 1]$'s (namely suffix starting from $s[i]$) longest common prefix (LCP) length.

## Examples
$z("aaaaa") = [0, 4, 3, 2, 1]$

$z("aaabaab") = [0, 2, 1, 0, 2, 1, 0]$

$z("abacaba") = [0, 0, 1, 0, 3, 0, 1]$

## Brute Force
$O(n^2)$

```C++
vector<int> z_function(const string &s) {
  vector<int> z(s.size());
  for (int i = 1; i < s.size(); ++i) {
    while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
  }
  return z;
}
```

## Optimized Algorithm
$O(n)$

Z-box: when calculating $z[i]$, we can make use of calculated $z[0], ..., z[i - 1]$, and these intervals are called z-box.

During the algorithm, we maintain the $[l, r]$, where $s[l, r]$ is prefix of s. We need to keep $l \leq i$. From the beginning, $l=r=0$.

During the process of calculating $z[i]$:
* if $i \leq r$, we have $s[i,r] = s[i-l, r-l]$. Therefore $z[i]\geq min(z[i - l], r- i +1)$, then
  * if $z[i-l]<r-i+1$, $z[i] = z[i-l]$
  * else we make $z[i]=r-i+1$, and enumerate the next characters until cannot expand $z[i]$ anymore.
* if $i>r$, do the same things as brute force
* after getting $z[i]$, if we have $i+z[i]-1>r$, we make $l=i, r=i+z[i]-1$.

```C++
vector<int> z_function(const string &s) {
  vector<int> z(s.size());
  for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
    if (i <= r && z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      z[i] = max(0, r - i + 1);
      while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) l = i, r = i + z[i] -1;
  }
  return z;
}
```

References: 

https://cp-algorithms.com/string/prefix-function.html

https://oi-wiki.org/string/kmp/