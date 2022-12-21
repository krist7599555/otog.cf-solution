// https://api.otog.cf/problem/doc/738
// วงล้อแห่งโชคชะตา (DinoWheel of Destiny)
// https://api.otog.cf/problem/doc/738
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <tuple>
#include <numeric>
// https://shainer.github.io/crypto/math/2017/10/22/chinese-remainder-theorem.html
using namespace std;
typedef unsigned long long lli;
#define rep(i,k,n) for(auto i = (k); i != (n); ++i)

inline int input() {
  int n; cin >> n; return n;
}

lli __lcm(lli a, lli b) {
  return a * b / __gcd<lli>(a, b);
}

int main() {
  cin.sync_with_stdio(false);
  int n; cin >> n;
  char c; cin >> std::ws >> c;
  std::vector<std::vector<bool>> inp;
  std::vector<lli> lcm(1, { 1 });

  rep(_, 0, n) {
    string s;
    cin >> s;
    lcm.emplace_back(__lcm(s.size(), lcm.back()));
    inp.emplace_back(s.size(), false);
    rep(i, 0, s.size()) {
      if (s[i] == c) {
        inp.back()[i] = true;
      }
    }
  }

  lli ans = 1e18;

  std::function<void(lli, lli)> recursive;
  recursive = [&](lli curr, int layer = 0) {
    if (curr > ans) return;
    if (layer == inp.size()) {
      ans = min(ans, curr);
      return;
    }
    for (lli jmp = 0; jmp < lcm[layer + 1]; jmp += lcm[layer]) {
      lli next = curr + jmp;
      if (inp[layer][next % inp[layer].size()]) {
        recursive(next, layer + 1);
      }
    }
  };
  recursive(1, 0);
  cout << ans << '\n';
}

/*
3 7
75483
713295734
721832395273541
=
15
*/
