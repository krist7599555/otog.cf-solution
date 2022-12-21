// https://api.otog.cf/problem/doc/696
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define all(x) x.begin(), x.end()
#define loop(i,n) for(int i = n; i--;)
using namespace std;
typedef long long lli;

inline int input() {
  int tmp; std::cin >> tmp; return tmp;
}

const int MXN = 1010;
std::vector<int> st[MXN];

int ans[MXN * 2];
int main() {
  int n = input();
  int m = input();
  for (int i = 1; i <= n; ++i) {
    loop(_, input()) {
      st[i].push_back(input());
    }
    std::sort(all(st[i]));
  }
  while (m--) {
    int a, b;
    char op;
    scanf("%d%c%d", &a, &op, &b);
    int* it;
    switch (op) {
    case 'U': it = std::set_union(all(st[a]), all(st[b]), ans); break;
    case '|': it = std::set_intersection(all(st[a]), all(st[b]), ans); break;
    case '-': it = std::set_difference(all(st[a]), all(st[b]), ans); break;
    }

    if (it == ans) {
      puts("Empty");
    }
    else {
      for (auto p = ans; p != it; ++p) {
        printf("%d ", *p);
      }
      putchar('\n');
    }
  }
}
