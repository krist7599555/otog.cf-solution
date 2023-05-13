// Matrix Exponentiation
// https://www.geeksforgeeks.org/matrix-exponentiation/
// https://codeforces.com/blog/entry/67776
// https://codeforces.com/blog/entry/80195
// https://usaco.guide/plat/matrix-expo?lang=cpp
// https://www.youtube.com/watch?v=eMXNWcbw75E
#include <vector>
#include <algorithm>
#include "stairs.h"

typedef long long lli;
#define rep(i, k, n) for (auto i = (k); i < (n); ++i)

const int MAXN = 100;
const lli MOD = 1e9 + 7;

struct Matrix{
  lli mtx[MAXN][MAXN];
  Matrix() {
    std::fill_n(mtx[0], MAXN * MAXN, 0);
  }
  lli& operator() (int i, int j) {
    return mtx[i][j];
  }
  lli operator() (int i, int j) const {
    return mtx[i][j];
  }
  friend Matrix operator* (const Matrix& lhs, const Matrix& rhs) {
    Matrix res;
    rep(i, 0, 100) {
      rep(j, 0, 100) {
        rep(k, 0, 100) {
          lli prod = (lhs(i,k) * rhs(k,j)) % MOD;
          res(i, j) = (res(i,j) + prod) % MOD;
        }
      }
    }
    return res;
  };
};

int countWays(lli n, int _, std::vector<int> steps){
  Matrix nextstep;
  rep(i, 1, MAXN) {
    nextstep(i, i - 1) = 1;
  }
  for (auto step: steps) {
    nextstep(0, step - 1) = 1;
  }

  Matrix ans;
  ans(0, 0) = 1;

  // exponential multiply
  for(; n != 0; n /= 2) {
    if (n % 2 == 1) ans = nextstep * ans;
    nextstep = nextstep * nextstep;
  }
  return ans(0, 0);
}
