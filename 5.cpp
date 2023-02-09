// 5
// https://api.otog.cf/problem/doc/5
#include <vector>
#include <iostream>
#include <cassert>

enum Scales { left, right, skip };

std::vector<Scales> scales_of(int weight) {
  std::vector<Scales> res; // res[i] is in multiply of pow(3, i)
  for (; weight > 0; weight /= 3) {
    switch (weight % 3) {
    case 0:
      res.push_back(Scales::skip);
      break;
    case 1:
      res.push_back(Scales::right);
      weight -= 1;
      break;
    case 2:
      res.push_back(Scales::left);
      weight += 1;
      break;
    }
  }
  return res;
}

int main() {
  int scales_left;
  std::cin >> scales_left;

  int scales_right = 0;
  int count_weighter = 0;
  int pow3 = 1;
  for (Scales fac : scales_of(scales_left)) {
    switch (fac) {
    case Scales::left:
      scales_left += pow3;
      count_weighter += 1;
      break;
    case Scales::right:
      scales_right += pow3;
      count_weighter += 1;
      break;
    case Scales::skip:;
    }
    pow3 *= 3;
  }
  assert(scales_right == scales_left);
  std::cout << count_weighter << ' ' << scales_left << std::endl;
}
