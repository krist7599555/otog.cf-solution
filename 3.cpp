// https://api.otog.cf/problem/doc/3
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
  int n = 0;
  std::cin >> n;
  while (n--) {
    int sum = 0;
    std::string inp;
    std::cin >> inp;
    std::vector<int> count(26, 0);
    for (char c : inp) {
      count[tolower(c) - 'a'] += 1;
    }
    std::sort(count.begin(), count.end(), std::greater<int>());
    int val = 26;
    for (int cnt : count) {
      sum += cnt * val--;
    }
    std::cout << sum << '\n';
  }
}
