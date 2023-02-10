// 5
// https://api.otog.cf/problem/doc/5
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>

enum Scales { lighter, heavier };
struct Mass {
  Scales scales;
  int weight;
};

std::vector<Mass> scales_of(const int weight) {
  std::vector<Mass> res; // res[i] is in multiply of pow(3, i)
  for (int mass = 1, wei = weight; wei > 0; wei /= 3, mass *= 3) {
    switch (wei % 3) {
    case 0: break;
    case 1:
      res.push_back({ Scales::heavier, mass });
      wei -= 1;
      break;
    case 2:
      res.push_back({ Scales::lighter, mass });
      wei += 1;
      break;
    }
  }

  {
    int mass_left = std::accumulate(res.begin(), res.end(), 0, [](int acc, Mass mass) {
      return acc + (mass.scales == Scales::lighter ? mass.weight : 0);
      });
    int mass_right = std::accumulate(res.begin(), res.end(), 0, [](int acc, Mass mass) {
      return acc + (mass.scales == Scales::heavier ? mass.weight : 0);
      });
    assert(mass_left + weight == mass_right);
  }
  return res;
}

int main() {
  int weight;
  std::cin >> weight;
  auto masses = scales_of(weight);
  std::cout << masses.size() << ' ' << std::accumulate(masses.begin(), masses.end(), 0, [](int acc, Mass mass) {
    return acc + (mass.scales == Scales::heavier ? mass.weight : 0);
    }) << std::endl;
}
