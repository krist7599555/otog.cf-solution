// 820 TOI18 Constellation
// https://api.otog.cf/problem/doc/820
// Rotate Grid in 45 degree + Quicksum2D + Combinatorics + Inverse Modular
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cassert>
#define rep(i, k, n) for (auto i = k; i != n; ++i)
#define Vec std::vector
typedef long long lli;
typedef std::pair<int, int> pii;

template<typename T>
T clamp(T val, T mn, T mx) {
  return std::min(std::max(val, mn), mx);
}

/**
 * QuickSum Diamon = QuickSum2D + Diagonal transform (Diamon = Rectangle in 45 degree)
 *
 * convert from
 *
 * ABC
 * DEF
 * GHI
 * JKL
 *
 * to
 *
 * .......
 * ...C...
 * ..B.F..
 * .A.E.I.
 * ..D.H.L
 * ...G.K.
 * ....J..
 */
struct QuickSumDiamon {
  static const int OFFSET_R = 1; // passing dp[0][_] = 0 for easy formula
  static const int OFFSET_C = 1; // passing dp[_][0] = 0 for easy formula
  const int input_row;
  const int input_col;
  const int size;
  Vec<Vec<int>> dp;

  QuickSumDiamon(int r, int c, const Vec<Vec<int>>& inp):
    input_row(r),
    input_col(c),
    size(r + c + OFFSET_R + OFFSET_C),
    dp(size, Vec<int>(size, 0)) {
    rep(i, 0, r) {
      rep(j, 0, c) {
        auto [ni, nj] = __coordinate(i, j); // copy value to new coordinate
        dp[ni][nj] = inp[i][j];
      }
    }

    // perform quicksum 2D http://nullzer0.wikidot.com/quicksum
    rep(i, 0, size) {
      rep(j, 0, size) {
        int sum_tt = i > 0 ? dp[i - 1][j] : 0; // top
        int sum_ll = j > 0 ? dp[i][j - 1] : 0; // left
        int sum_tl = i > 0 && j > 0 ? dp[i - 1][j - 1] : 0; // top-left
        dp[i][j] += sum_tt + sum_ll - sum_tl;
        // dp'[i][j] = sum { dp[0..i][0..j] }
      }
    }

    // ensure border of dp is 0
    rep(i, 0, size) {
      assert(dp[i][0] == 0);
      assert(dp[0][i] == 0);
    }
  }

public:

  /*
    sum area in shape of
               j
      ......xxxxxxx....
      .......xxxxx.....
      ........xxx......
    i .........x.......
      .................
  */
  int area_inverse_piramit(int i, int j) const {
    auto [i2, j2] = __coordinate(i, j);
    return __area_inverse_piramit(i2, j2);
  }

  /*
    sum area in shape of diamon

    example (distance = 2)
               j
      .................
      .........x.......
      ........xxx......
    i .......xxxxx.....
      ........xxx......
      .........x.......
      .................
  */
  int area_diamon(int i, int j, int distance) const {
    auto [i_outer, j_outer] = __coordinate(i + distance, j);
    auto [i_inner, j_inner] = __coordinate(i - distance, j);
    i_inner -= 1;
    j_inner -= 1;
    assert(i_inner <= i_outer);
    assert(j_inner <= j_outer);
    // A union B = A + B - (A intersect B)
    return
      __area_inverse_piramit(i_outer, j_outer)
      - __area_inverse_piramit(i_outer, j_inner)
      - __area_inverse_piramit(i_inner, j_outer)
      + __area_inverse_piramit(i_inner, j_inner);
  }

private:
  /* safe quick sum 2d in interal coordinate */
  int __area_inverse_piramit(int i, int j) const {
    return dp[clamp(i, 0, size - 1)][clamp(j, 0, size - 1)];
  }
  /*
    convert input cooridinate to internal coordinate
    i' = i - j
    j' = i + j
  */
  pii __coordinate(int i, int j) const {
    return pii(i - j + input_col - 1 + OFFSET_R, i + j + OFFSET_C);
  }
};

struct NChooseK {
  virtual int n_choose_k(int n, int k) const = 0;
};

#ifdef ADVANCE_SOLUTION
/*
  ModularSystem
  precalculate all value in MOD system
  can use for compute precalculate Pascal's triangle / Binomial coefficient / N choose K
*/
struct ModularSystem: NChooseK {
  // https://vnspoj.github.io/wiki/algebra/module-inverse
  // http://e-maxx.ru/algo/reverse_element (https://e--maxx-ru.translate.goog/algo/reverse_element?_x_tr_sch=http&_x_tr_sl=en&_x_tr_tl=th&_x_tr_hl=en&_x_tr_pto=wapp)
  int mod;
  Vec<lli> inv;
  Vec<lli> fac;
  Vec<lli> ifac;
  ModularSystem(int _mod): mod(_mod), inv(mod), fac(mod), ifac(mod) {
    inv[1] = 1;
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i < mod; ++i) {
      inv[i] = mod - (mod / i) * inv[mod % i] % mod;
      fac[i] = (fac[i - 1] * i) % mod;
      ifac[i] = (ifac[i - 1] * inv[i]) % mod;
    }
  }
  int n_choose_k(int n, int k) const {
    if (k > n) return 0;
    return ((fac[n] * ifac[n - k]) * ifac[k]) % mod;
  }
};

#else

struct PascalTriangle: NChooseK {
  int mod;
  int size;
  Vec<Vec<int>> pascal;
  PascalTriangle(int mod, int size): mod(mod), size(size) {
    pascal.resize(size);
    rep(n, 0, size) {
      pascal[n].resize(n + 1, 1);
      rep(k, std::min(1, n), n) {
        pascal[n][k] = (pascal[n - 1][k - 1] + pascal[n - 1][k]) % mod;
      }
    }
  }
  int n_choose_k(int n, int k) const {
    if (k > n) return 0;
    if (n > pascal.size()) puts("bad");
    if (k > pascal[n].size()) puts("bad2");
    return pascal[n][k] % mod;
  }
};
#endif

int main() {
  int r, c, k;
  std::cin >> r >> c >> k;
  Vec<Vec<int>> inp(r, Vec<int>(c, 0));
  rep(i, 0, r) {
    std::string str;
    std::cin >> str;
    rep(j, 0, c) {
      inp[i][j] = str[j] == '#' ? 1 : 0;
    }
  }
  const auto diamon = QuickSumDiamon(r, c, inp);
#ifdef ADVANCE_SOLUTION
  const auto combi = ModularSystem(1'000'003); // hardway but cool O(mod)
#else
  const auto combi = PascalTriangle(1'000'003, 2 * r + 2 * c); // easy way but fixed solution O(size)
#endif

  int ans = 0;
  rep(i, 0, r) {
    rep(j, 0, c) {
      rep(d, 0, r + c) {
        auto area_inner = diamon.area_diamon(i, j, d);
        auto area_outer = diamon.area_diamon(i, j, d + 1);
        assert(area_outer >= area_inner);
        int count_star = area_outer - area_inner;
        ans = (ans + combi.n_choose_k(count_star, k)) % combi.mod;
      }
    }
  }
  printf("%d\n", ans);
}
