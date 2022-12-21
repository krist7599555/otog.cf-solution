// https://api.otog.cf/problem/doc/698
#include <iostream>
#include <vector>
#include <algorithm>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long lli;

inline int input() {
  int tmp; std::cin >> tmp; return tmp;
}

struct Bignum {
  std::vector<int> mData;
  Bignum(int i = 0) {
    while (i) {
      mData.push_back(i % 10);
      i /= 10;
    }
  }
  void operator+=(const Bignum& rhs) {
    int carry = 0;
    int lsz = mData.size();
    int rsz = rhs.mData.size();
    for (int i = 0; i < rsz; ++i) {
      if (i >= lsz) {
        mData.push_back(0);
      }
      mData[i] += rhs.mData[i] + carry;
      carry = mData[i] / 10;
      mData[i] %= 10;
    }
    if (carry) {
      mData.push_back(carry);
    }
  }
  friend std::ostream& operator<<(std::ostream& o, const Bignum& bg) {
    int i = bg.mData.size();
    if (i == 0) return o << '0';
    while (i--) {
      o << bg.mData[i];
    }
    return o;
  }
};

int main() {
  std::vector<int> acc = {0};
  std::vector<Bignum> fib;
  Bignum fib0 = 1, fib1 = 1;
  for (int i = 0; acc.back() <= 1e6; ++i) {
    acc.push_back(acc.back() + i * 2 + 1);
    fib.push_back(fib0);
    std::swap(fib0, fib1);
    fib0 += fib1;
  }
  int n = input();
  while (n--) {
    auto it = std::upper_bound(all(acc), input() - 1);
    std::cout << fib[it - acc.begin() - 1] << '\n';
  }
}