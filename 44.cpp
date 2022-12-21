// คู่ตัวเลขเด่น (Pair)
// https://api.otog.cf/problem/doc/44
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lli;
#define rep(i,k,n) for(auto i = (k); i != (n); ++i)

inline int input() {
  int n; cin >> n; return n;
}

struct Data {
  lli a;
  int b;
  int count;
  Data(lli _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), count(_c) {}
};

template<typename T, typename FixupFunc>
struct SegmentTree {
  const int n;
  const FixupFunc fixup;
  std::vector<T> seg;

  SegmentTree(int _n, FixupFunc _fixup):
    n(1 << int(ceil(log2(_n)))), // use n as 2^x
    fixup(_fixup) {
    seg.resize(2 * n);
    for (int i = n - 1; i >= 1; --i) {
      seg[i] = fixup(seg[i * 2], seg[i * 2 + 1]);
    }
  }

  void update(int index, T val) {
    int i = n + index; // go to leaf
    seg[i] = val;
    i /= 2;
    for (; i >= 1; i /= 2) {
      seg[i] = fixup(seg[i * 2], seg[i * 2 + 1]);
    }
  }

  template<typename F>
  void _travel(int i, int l, int r, int findl, int findr, F fun) { // [left, right]
    // current node
    if (findl <= l && r <= findr) {
      fun(seg[i]);
      return;
    }
    // go left and right
    int m = (l + r) / 2;
    if (findl < m) _travel(i * 2 + 0, l, m, findl, findr, fun); // left
    if (m < findr) _travel(i * 2 + 1, m, r, findl, findr, fun); // right
  }

  template<typename F>
  void travel(int left, int right, F fun) { // [left, right]
    return _travel(1, 0, n, left, right, fun);
  }

};

int main() {
  cin.sync_with_stdio(false);
  const int n = input();
  std::vector<Data> inp;
  rep(i, 0, n) {
    int a = input();
    int b = input() - 1;
    assert(b <= n);
    inp.push_back(Data(a, b, 1));
  }
  std::sort(inp.begin(), inp.end(), [](const Data& lhs, const Data& rhs) {
    return lhs.a > rhs.a;
    });

  auto data_sum = [](const Data& lhs, const Data& rhs) {
    return Data(lhs.a + rhs.a, lhs.b + rhs.b, lhs.count + rhs.count);
  };
  SegmentTree<Data, decltype(data_sum)> seg(n, data_sum);
  lli ans = 0;
  for (Data& data : inp) {
    lli sum_a = 0;
    int count = 0;
    seg.travel(0, data.b, [&](const Data& node) {
      sum_a += node.a;
    count += node.count;
      });
    ans += sum_a + lli(data.a) * count;

    seg.update(data.b, data);
  }
  printf("%lld\n", ans);
}
