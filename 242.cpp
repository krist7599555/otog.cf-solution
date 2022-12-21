// https://api.otog.cf/problem/doc/242
#include <iostream>
#define rep(i,k,n) for(auto i = k; i!=n;++i)
#define loop(i,n) for(auto i = n; i--;)
using namespace std;

template<typename T = int>
T input() { T tmp; std::cin >> tmp; return tmp; }

int main() {
  char mat[10];
  int patt[][3] = {
    {0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6},
  };

  loop(_, input()) {
    rep(i, 0, 3) scanf("%s", mat + i * 3);

    for (char c : "OX") {
      for (auto& pos : patt) {
        int cnt = 0;
        int dot = -1;
        for (int p : pos) {
          if (mat[p] == c) ++cnt;
          if (mat[p] == '.') dot = p;
        }
        if (dot != -1 && cnt == 2) {
          printf("%d %d\n", dot / 3 + 1, dot % 3 + 1);
          goto next;
        }
      }
    }
  next:;
  }
}
