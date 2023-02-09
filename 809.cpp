// 809 ผีถ้วยแก้ว
// https://api.otog.cf/problem/doc/809
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <map>
using namespace std;
#define rep(i,k,n) for(auto i = (k); i != (n); ++i)
typedef std::pair<int, int> pii;

const pii ZERO_PII = pii(0, 0);
const int MAXN = 200;
const int MOD = 1000000007;
inline int pos(int i, int j) {
  return i * MAXN + j;
}

// posa = 0..200
// dp[t][posa][posb] =
//   + (dp[t-1][posa-1][posb] * dp[t-1][posa][posb-1])
//   + (dp[t-1][posa+1][posb] * dp[t-1][posa][posb+1])

// total - dup
// dup if stay on same position and go to same direction

// ans(a, b)
//     = way from two 0,0 to a,b without overlab
//     =

std::map<std::pair<pii, pii>, int> memo_solve;
int solve(pii a, pii b) {
  if (a == ZERO_PII && b == ZERO_PII) return 1;
  auto it = memo_solve.find({ a, b });
  if (it == memo_solve.end()) {
    it = memo_solve.find({ b, a });
  }
  if (it != memo_solve.end()) {
    return it->second;
  }
  int ans = 0;
  for (auto ax : { pii(a.first - 1, a.second), pii(a.first, a.second - 1) }) {
    for (auto bx : { pii(b.first - 1, b.second), pii(b.first, b.second - 1) }) {
      if (std::min({ ax.first, ax.second, bx.first, bx.second }) >= 0) {
        if (a == b && ax == bx) continue; // from same position to same position = invalid
        ans += solve(ax, bx);
      }
    }
  }
  // std::cerr << a.first << ',' << a.second << " " << b.first << ',' << b.second << " = " << ans << std::endl;
  memo_solve[{ a, b }] = ans;
  return ans;
}

int solve(int r, int c) {
  return solve(pii(r - 1, c - 1), pii(r - 1, c - 1));
}

int n_choose_k(int n, int k) {
  if (k > n) return 0;
  if (k * 2 > n) k = n - k;
  if (k == 0) return 1;

  int result = n;
  for (int i = 2; i <= k; ++i) {
    result *= (n - i + 1);
    result /= i;
  }
  return result;
}

int main() {
  // int row;
  // int col;
  // std::cin >> row >> col;
  // assert(row <= 200);
  // assert(col <= 100000);
  // std::vector<int> step(MAXN);
  rep(i, 1, 10) {
    rep(j, 1, i + 1) {
      auto choose = n_choose_k(i + j - 2, i - 1) * n_choose_k(i + j - 2, i - 1);
      std::cout << choose - solve(i, j) << ' ';
    }
    std::cout << '\n';
  }
}
