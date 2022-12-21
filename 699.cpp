// https://api.otog.cf/problem/doc/699
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#define loop(i,n) for(int i = 0; i != n; ++i)
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long lli;

inline int input() {
  int tmp; std::cin >> tmp; return tmp;
}

int main() {
  int a = input();
  int b = input();
  std::vector<int> prime;
  std::vector<int> remain;
  loop(i, 8) prime.push_back(input());
  loop(i, 8) remain.push_back(input());

  // answer is in form [lcm * x + rem]
  lli lcm = 1;
  for (int p : prime) {
    lcm *= p;
  }
  lli rem = remain.back();
find_proper_remain:
  for (int i = 0; i != 8; ++i) {
    if (rem % prime[i] != remain[i]) {
      rem += prime.back();
      goto find_proper_remain;
    }
  }

  int cnt = 0;
  while (rem <= b) {
    if (a <= rem) {
      cnt += 1;
    }
    rem += lcm;
  }
  printf(cnt ? "%d\n" : "saddo\n", cnt);
}
