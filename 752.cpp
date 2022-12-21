// otog 752 นักเก็บเงิน
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Query {
  int index;
  int amount;
  int answer; // day
};

const int MAX_SIZE = 1e5 + 1;

int inp[MAX_SIZE];
Query query[MAX_SIZE];

inline int input() {
  int i; std::cin >> i; return i;
}

#define rep(i, n) for(int i = 0; i != n; ++i)

int main() {
  cin.sync_with_stdio(false);
  const int n = input();
  const int q = input();
  rep(i, n) {
    inp[i] = input();
  }
  rep(i, q) {
    query[i].index = i;
    query[i].answer = -1;
    query[i].amount = input();
  }

  // sort query for easy collacted coin to hard collacted
  std::sort(query, query + q, [](const Query& lhs, const Query& rhs) {
    return lhs.amount < rhs.amount;
    });

  long long sum = 0;
  int query_index = 0;
  rep(day, n) {
    sum += inp[day]; // collect coin
    while (query_index < q and query[query_index].amount <= sum) {
      query[query_index++].answer = day;
    }
  }

  // sort back answer
  std::sort(query, query + q, [](const Query& lhs, const Query& rhs) {
    return lhs.index < rhs.index;
    });
  rep(i, q) {
    printf("%d\n", query[i].answer);
  }
}
