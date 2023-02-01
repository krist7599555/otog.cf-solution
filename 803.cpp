// https://api.otog.cf/problem/doc/803
// dynamic programming
#include <iostream>
#include <algorithm>
#include <numeric>
#define loop(i,s,t) for(int i = (s); i != (t); ++i)
using namespace std;

template <typename T = int>
inline T input() {
  T tmp; std::cin >> tmp; return tmp;
}

const int MAXN = 200;
const int MAXR = MAXN + MAXN + 1;
const int MOD = 10000009;
const int ZERO[MAXR + 1] = {};
int dp[MAXN][MAXN][MAXR + 1] = {};
/*
  dp[i][j][x] = number of possible path walk from (0,0) to (i,j) that use exacly (x) lifepoint
  dp[0][0][0] = 1
  dp[i][j][x] =
    if inp[i][j] == # then 0
    if inp[i][j] == X then dp[i-1][j][x-1] + dp[i][j-1][x-1]
    if inp[i][j] == . then dp[i-1][j][x] + dp[i][j-1][x]
*/

int main() {
  const int row = input();
  const int col = input();
  const int life = input();
  auto add = [](int a, int b) { return (a + b) % MOD; };

  loop(i, 0, row) {
    auto inp = input<std::string>();
    loop(j, 0, col) {
      if (inp[j] == '#') continue;
      if (i == 0 && j == 0) {
        dp[0][0][0] = 1;
      } else {
        const int* top = j > 0 ? dp[i][j - 1] : ZERO;
        const int* left = i > 0 ? dp[i - 1][j] : ZERO;
        int* output = dp[i][j] + (inp[j] == 'X' ? 1 : 0);
        std::transform(top, top + MAXR, left, output, add);
      }
    }
  }

  std::cout << std::accumulate(dp[row - 1][col - 1], dp[row - 1][col - 1] + life + 1, 0, add) << std::endl;
}

/*in1
3 3 1
.X.
..X
#..
*/

/*out1
3
*/

/*in2
7 9 2
...#.....
X.X#####X
.......X.
......X..
..X##X...
.#..###..
.........
*/

/*out2
329
*/
