// 10
// https://api.otog.cf/problem/doc/10
// sliding window
#include <iostream>
#include <algorithm>
#include <cassert>

int main() {
  int n, max_distance;
  std::cin >> n >> max_distance;

  int ans = 0;
  int inp[n];
  for (int i = 0, last_idx = 0; i < n; ++i) {
    std::cin >> inp[i];
    assert(i == 0 || inp[i - 1] < inp[i]);
    while (last_idx < i && inp[i] - inp[last_idx] > max_distance) {
      last_idx += 1;
    }
    ans = std::max(ans, i - last_idx);
  }
  std::cout << ans << std::endl;
}
