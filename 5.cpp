// 5
// https://api.otog.cf/problem/doc/5
#include <vector>
#include <iostream>

std::vector<int> factor_of3(int num) {
  std::vector<int> res;
  for (; num > 0; num /= 3) {
    switch (num % 3) {
    case 0:
      res.push_back(0);
      break;
    case 1:
      res.push_back(1);
      num -= 1;
      break;
    case 2:
      res.push_back(-1);
      num += 1;
      break;
    }
  }
  return res;
}

int main() {
  int inp;
  std::cin >> inp;
  auto fac = factor_of3(inp);
  int rem = 0; // remaining
  for (int i = 0, pow3 = 1; i < fac.size(); ++i, pow3 *= 3) {
    if (fac[i] == -1) {
      inp += -fac[i] * pow3; // weight on input side
    } else if (fac[i] == 1) {
      // weight on another side
      rem += fac[i] * pow3;
    }
  }
  assert(rem == inp);
  std::cout << fac.size() << ' ' << inp << std::endl;
}
