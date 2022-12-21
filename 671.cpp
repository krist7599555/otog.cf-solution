// https://api.otog.cf/problem/doc/671
#include <iostream>
#define loop(i,n) for(auto i = n; i--;)
using namespace std;

template<typename T = int>
T input() { T tmp; std::cin >> tmp; return tmp; }

int main() {
  int c, h;
  char s[][7] = { "Alkane", "Alkene", "Alkyne" };
  loop(_, input()) {
    scanf(" %*[C] %d %*[H] %d", &c, &h);
    puts(s[c - h / 2 + 1]);
  }
}
