// 822 Toi18 Sai-ua
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

int solve_stdin(std::istream& stdin) {
  int n; stdin >> n;
  std::vector<int> inp(n);
  rep(i, 0, n) stdin >> inp[i];


  std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
  // dp(i, j)
  //   = sum maximum difference in range [i,j]
  //   = abs(inp(i)-inp(j)) + max{ dp(i, j-1), dp(i+1, j) }
  rep(sz, 2, n + 1) {
    for (int i = 0, j = sz - 1; j < n; ++i, ++j) {
      dp[i][j] = abs(inp[j] - inp[i]) + std::max(dp[i][j - 1], dp[i + 1][j]);
    }
  }

  std::vector<int> dp2(n, 0);
  // dp2(i)
  //   = answer in range [0,i] (may have multiple chunk)
  //   = max { j < i | dp2(j - 1) + dp(j, i) }
  rep(i, 0, n) {
    rep(j, 0, i) {
      dp2[i] = std::max(dp2[i], (j > 0 ? dp2[j - 1] : 0) + dp[j][i]);
    }
  }

  int ans = dp2[n - 1] + std::accumulate(inp.begin(), inp.end(), 0);
  return ans;
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
