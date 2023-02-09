// 822 Toi18 Sai-ua (Top Down Solution)
// https://api.otog.cf/problem/doc/822
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <istream>
#include <numeric>
#include <cassert>
using namespace std;
#define rep(i,k,n) for(auto i = (k); i != (n); ++i)

const int MAXN = 5000;

// dp(i, j)
//   = sum maximum difference in range [i,j]
//   = abs(inp(i)-inp(j)) + max{ inp(j)+dp(i, j-1), inp(i)+dp(i+1, j) }
int dp[MAXN][MAXN] = {};
int maximum_magic_sum(const std::vector<int>& inp, int l, int r) {
  if (l > r) return 0;
  if (dp[l][r] > 0) return dp[l][r];
  return dp[l][r] = abs(inp[l] - inp[r]) + std::max(
    inp[r] + maximum_magic_sum(inp, l, r - 1),
    inp[l] + maximum_magic_sum(inp, l + 1, r)
  );
}

// dp2(i)
//   = answer in range [0,i] (may have multiple chunk)
//   = max { j < i | dp2(j - 1) + dp(j, i) }
int dp2[MAXN] = {};
int solve_siua(const std::vector<int>& inp, int r) {
  if (r < 0) return 0;
  if (dp2[r] > 0) return dp2[r];
  int ans = 0;
  rep(l, 0, r) {
    ans = std::max(ans, 0 + solve_siua(inp, l - 1) + maximum_magic_sum(inp, l, r));
  }
  return dp2[r] = ans;
}

int solve_stdin(std::istream& stdin) {
  int n; stdin >> n;
  std::vector<int> inp(n);
  rep(i, 0, n) stdin >> inp[i];
  std::fill_n(dp[0], MAXN * MAXN, 0);
  std::fill_n(dp2, MAXN, 0);
  return solve_siua(inp, n - 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  auto test0 = std::istringstream("4  1 2 3 6");
  assert(24 == solve_stdin(test0));

  auto test1 = std::istringstream("7  16 16 3 3 5 19 19");
  assert(153 == solve_stdin(test1));

  auto test2 = std::istringstream("6  16 4 30 20 21 7");
  assert(171 == solve_stdin(test2));

  auto test3 = std::istringstream("8  15 5 8 10 10 3 11 10");
  assert(120 == solve_stdin(test3));

  auto test4 = std::istringstream("5  5 8 5 11 2");
  assert(52 == solve_stdin(test4));

  std::cout << solve_stdin(std::cin) << std::endl;
}
