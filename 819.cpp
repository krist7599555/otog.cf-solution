// 819
// https://api.otog.cf/problem/doc/819
// longest increasing subsequence end with each position
#include <iostream>
#include <vector>
#include <algorithm>
#define loop(i,n) for(int i = 0; i != n; ++i)
#define all(a) (a).begin(), (a).end()
using namespace std;
typedef std::vector<int> Vec;

inline int input() {
  int tmp; std::cin >> tmp; return tmp;
}

Vec longest_increasing_subsequence(Vec inp) {
  Vec ans; // ans[i] = maximum subsequence length end with i
  Vec dp; // dp[i] = at current time; minimum value that can create LIS size = i
  for (auto val : inp) {
    auto it = std::lower_bound(all(dp), val);
    ans.push_back(std::distance(dp.begin(), it));
    if (it != dp.end()) {
      *it = val; // extends LIS sequence from it-1
    } else {
      dp.push_back(val); // extends LIS sequence from it-1
    }
  }
  return ans;
}

Vec reverse(const Vec& arr) {
  Vec res(arr);
  std::reverse(all(res));
  return res;
}

int main() {
  std::cin.sync_with_stdio(false);
  int n = input();
  int q = input();
  Vec tree(n);
  loop(i, n) {
    tree[i] = input();
  }
  Vec longest_inc_seq = longest_increasing_subsequence(tree);
  Vec longest_dec_seq = reverse(longest_increasing_subsequence(reverse(tree)));
  loop(_, q) {
    int pos = input();
    std::cout << std::min(longest_inc_seq[pos], longest_dec_seq[pos]) << '\n';
  }
}
