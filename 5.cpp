// 5
// https://api.otog.cf/problem/doc/5
#include <vector>
#include <iostream>
#include <cassert>

enum Scales { lighter, heavier, skip };

std::vector<Scales> scales_of(int weight) {
  std::vector<Scales> res; // res[i] is in multiply of pow(3, i)
  for (; weight > 0; weight /= 3) {
    switch (weight % 3) {
    case 0:
      res.push_back(Scales::skip);
      break;
    case 1:
      res.push_back(Scales::heavier);
      weight -= 1;
      break;
    case 2:
      res.push_back(Scales::lighter);
      weight += 1;
      break;
    }
  }
  return res;
}

int main() {
  int total_weight_left;
  std::cin >> total_weight_left;

  int total_weight_right = 0;
  int count_mass_use = 0;
  int pow3 = 1;
  for (Scales mass : scales_of(total_weight_left)) {
    switch (mass) {
    case Scales::lighter:
      total_weight_left += pow3;
      count_mass_use += 1;
      break;
    case Scales::heavier:
      total_weight_right += pow3;
      count_mass_use += 1;
      break;
    case Scales::skip:;
    }
    pow3 *= 3;
  }
  assert(total_weight_right == total_weight_left);
  std::cout << count_mass_use << ' ' << total_weight_left << std::endl;
}
