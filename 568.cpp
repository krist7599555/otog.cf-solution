#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <cmath>
#include <cassert>
#define input() (*std::istream_iterator<int>(std::cin))
#define rep(i,k,n) for (auto i = k; i != n; ++i)

struct Data {
  int value, cost;
  int sum_value, sum_cost;
  double upperbound;
  Data(int v, int c): value(v), cost(c), sum_value(v), sum_cost(c), upperbound(c ? double(v) / c : 0.0) {}
  bool operator > (const Data& rhs) const { return upperbound > rhs.upperbound; }
};
typedef std::vector<Data>::iterator It;

struct Node {
    It  it;
    int upperbound, money, value;
    Node(It i, int u, int m, int v): it(i), upperbound(u), money(m), value(v){}
    bool operator < (const Node& rhs) const {return upperbound < rhs.upperbound;}
};

int main(){
  std::cin.sync_with_stdio(0);

  int n = input();
  std::vector<Data> in;
  rep(i,0,n){
    int v = input();
    int c = input();
    in.emplace_back(v, c);
  }
  // sort by greater exchange ratio -greedy-
  // quick sum valueue and cost
  std::sort(in.begin(), in.end(), std::greater<Data>());
  in.insert(in.begin(), Data(0, 0));
  rep(i,1,n){
    in[i+1].sum_value += in[i].sum_value,
    in[i+1].sum_cost += in[i].sum_cost;
  }

  // heuristic always be upper bound of optimial cost
  // 0-1 knapsack on [l, r) with money
  auto heuristic = [&in](It l, It r, int money) -> int {
    if (l == r) return 0;
    assert(in.begin() <= l && r <= in.end());
    int cost_find = l[-1].sum_cost + money;
    auto it = std::upper_bound(l, r, cost_find, [](int vl, const Data& d){ return vl < d.sum_cost; });
    return it[-1].sum_value - l[-1].sum_value + (it == r ? 0.0D : std::ceil(it[0].upperbound * (cost_find - it[-1].sum_cost)));
  };

  int lm = input();
  int sz = input();
  std::vector<int> ans;
  std::priority_queue<Node> pq;
  pq.emplace(in.begin() + 1, heuristic(in.begin() + 1, in.end(), lm), lm, 0);

  // 0-1 knapsack O(2^n) with pruning
  // ordering by maximum valueue ratio for greedy
  while (!pq.empty() and ans.size() != sz){
    Node nd = pq.top(); pq.pop();
    if (nd.it == in.end()){ // finish iterator through n element
      ans.push_back(nd.value);
    } else {
      if (nd.money >= nd.it->cost) {
        pq.emplace(nd.it + 1, nd.upperbound, nd.money - nd.it->cost, nd.value + nd.it->value); // 1
      }
      pq.emplace(nd.it + 1, nd.value + heuristic(nd.it + 1, in.end(), nd.money), nd.money, nd.value); // 0
    }
  }
  ans.resize(sz, 0);
  for (int i : ans){
    printf ("%d\n", i);
  }
}
