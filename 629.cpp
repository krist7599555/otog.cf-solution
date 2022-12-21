// https://api.otog.cf/problem/doc/629
#include <iostream>
#include <algorithm>
#include <vector>

const int N = 2002;
const int M = 10003;
char inp[N][M];
const char EMPTY = '0';
const char STAR = '1';

int remove_star(int i, int j) {
  std::vector<int> memo;
  while (inp[i][j] == STAR) {
    // std::cout << "start " << i << ' ' << j << '\n';
    while (inp[i][j - 1] == STAR) j -= 1;
    char* l = &inp[i][j];
    char* r = l;
    while (*r == STAR) ++r;
    memo.push_back(std::distance(l, r));
    std::fill(l, r, EMPTY);

    bool have_next = false;
    for (int d = j - 1; d <= j + 1; ++d) {
      if (inp[i + 1][d] == STAR) {
        i = i + 1;
        j = d;
        have_next = true;
        break;
      }
    }
    if (!have_next) break;
  }
  int top = memo[0];
  int top_second = memo[1];
  int bot = memo[memo.size() - 1];
  if (top == bot && top > 1) return 1; // square
  if (top == 1 && bot == 1 && top_second == 3) return 2; // diamon
  return 3;
}

int main() {
  int r, c;
  std::cin.sync_with_stdio(false);

  while (std::cin >> c >> r) {
    std::vector<int> ans(4, 0);
    std::fill_n(inp[0], N * M, EMPTY);
    for (int i = 1; i <= r; ++i) {
      std::cin >> (inp[i] + 1);
      inp[i][c + 1] = EMPTY;
      inp[i][c + 2] = 0;
    }
    inp[0][c + 2] = 0;
    inp[r + 1][c + 2] = 0;

    // for (int i = 0; i <= r+1; ++i) {
    // 	std::cout << inp[i] << '\n';
    // }
    // std::cout << "----\n";

    for (int i = 1; i <= r; ++i) {
      for (int j = 1; j <= c; ++j) {
        if (inp[i][j] == STAR) {
          int kind = remove_star(i, j);
          ans[kind] += 1;

          // for (int k = 0; k <= r+1; ++k) {
          // 	std::cout << inp[k] << '\n';
          // }
          // std::cout << "----\n";
        }
      }
    }
    std::cout << ans[1] << ' ' << ans[2] << ' ' << ans[3] << '\n';
  }

  return 0;
}

/*
20 12
00000000000000000000
00100000001111111110
01110000000111111100
11111000000011111000
00000000000001110000
00000000000000100000
00000000000000000000
00011111000000000000
00011111000000000000
00011111000000000000
00011111000000000000
00011111000000000000
20 12
00000000000000000000
10000000001111111110
11000100000111111100
11101110000011111000
11000000000001110000
10000000000000100000
00000000000000000000
11111000000000100000
11111000000001110000
11111000000011111000
11111000000001110000
11111000000000100000
20 12
00000000000000000000
10000000001111111110
11000100000111111100
11101110000011111000
11000000000001110000
10000000000000100000
00000000000000000110
00011111000001000110
00011111000011100000
00011111000111110111
00011111000011100111
00011111000001000111
*/

/**
1 0 2
1 1 3
3 1 3
*/
