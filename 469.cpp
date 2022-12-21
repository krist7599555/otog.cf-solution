// https://api.otog.cf/problem/doc/469
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  std::string inp;
  while (std::cin >> n >> inp) {
    std::vector<int> kmp(n, 0);
    int rep = 0;
    for (int i = 1; i < n; ++i) {
      while (rep > 0 && inp[i] != inp[rep]) {
        rep = kmp[rep - 1];
      }
      kmp[i] = inp[i] == inp[rep] ? ++rep : 0;
    }

    int ans = n - kmp[n - 1];
    bool valid_answer = 2 * ans <= n && n % ans == 0;

    // for (int i = 0; i < n; ++i) {
    // 	std::cout << kmp[i] << ' ';
    // }
    // std::cout << '\n';
    // std::cout << "= ";
    std::cout << (valid_answer ? ans : n) << '\n';
  }
  return 0;
}
