// https://api.otog.cf/problem/doc/689
#include <iostream>
#include <vector>
using namespace std;
typedef long long lli;

inline int input() {
  int tmp; std::cin >> tmp; return tmp;
}

/*
y = (A(10 ** (2+14x)) − B) / C
Python3
A = 542000423599306
B = 29700042359930845
C = 699999999999993
for i in range(1, 8):
  ans = (A * (10 ** (2 + 14 * i)) - B) // C
  print(i, ans)
*/
/*
1 7742863194275835
2 774286319427587742863194275835
3 77428631942758774286319427587742863194275835
4 7742863194275877428631942758774286319427587742863194275835
5 774286319427587742863194275877428631942758774286319427587742863194275835
*/



int main() {
  int m = input();
  lli n = input();
  switch (m) {
  case 1: // sum
    printf("%llu", 73 * n + 8);
    break;
  case 2: // print
    while (n--) {
      printf("77428631942758");
    }
    puts("35");
    break;
  }
}
