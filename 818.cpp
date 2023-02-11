// 818 TOI18 Mountain
// https://api.otog.cf/problem/doc/818
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <map>
#include <climits>
using namespace std;

#define x first
#define y second
#define rep(i,k,n) for (auto i = (k); i != (n); ++i)
typedef long long lli;
typedef std::pair<lli, lli> Point;

lli input() {
  lli inp; std::cin >> inp; return inp;
}

lli distance(const Point& lhs, const Point& rhs) {
  return abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y);
}

const int MAXN = 500;
const lli INF = LONG_MAX - 1;


int main() {
  // else if (__cplusplus == 201103L) std::cout << "C++11\n";
  // else if (__cplusplus == 199711L) std::cout << "C++98\n";
  // else std::cout << "pre-standard C++\n";

  const int n = input();
  const int q = input();

  std::vector<Point> points;
  rep(_, 0, n) {
    points.emplace_back(input(), input());
  }

  lli dp[MAXN][MAXN];
  // dp(node, food) = minimum human power use for walk from 0 to `node` with `food` provide
  // dp(0, 0) = 0
  // dp(_, 0) = INF
  // dp(n, f) = min { n2 in nodes | max(dp(n2, food - 1), distance(n2, n)) }
  std::fill_n(dp[0], MAXN * MAXN, INF);
  dp[0][0] = 0;

  rep(food, 1, n) {
    rep(node, 0, n) {
      dp[node][food] = INF;
      dp[node][food] = dp[node][food - 1]; // optimize monotonic
      rep(node2, 0, n) {
        if (node != node2) {
          dp[node][food] = std::min(
            dp[node][food],
            std::max(dp[node2][food - 1], distance(points[node], points[node2]))
          );
        }
      }

    }
  }

  const lli* foods = dp[n - 1];
  lli ans = 0;
  rep(_, 0, q) {
    lli max_walk = input();
    auto it = std::lower_bound(foods, foods + n, max_walk, std::greater<lli>());
    ans += std::distance(foods, it);
  }
  std::cout << ans << std::endl;
}

/*
5 2
0 1
2 2
3 6
6 6
9 10
10
15
---
4
*/

/*
5 2
0 1
2 2
3 6
6 6
9 10
10
30
---
3
*/

/*
5 2
0 0
2 0
7 0
4 0
10 0
10
3
---
5
*/
