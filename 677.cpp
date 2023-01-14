// กรีดยางอย่างหนัก
// https://api.otog.cf/problem/doc/677
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <bitset>
#include <iomanip>
using namespace std;
template<typename T = int>
inline T input() { T tmp; std::cin >> tmp; return tmp; }
#define fori(i,s,t) for (auto i = (s); i != (t); ++i)


#define FEATURE_BACKTRACK

typedef std::bitset<30> Bits;

struct Edge {
  char direction;  // for debug - can remove
  int position;
  Edge(char d, int p): direction(d), position(p) {}
};

struct Node {
  int last_position;
  int life_point;
  Bits visits;
  string backtrack; // for debug - can remove
  Node(int pos, int lp, Bits vis, string bt): last_position(pos), life_point(lp), visits(vis), backtrack(bt) {
#ifndef FEATURE_BACKTRACK
    backtrack = "";
#endif
  }

  // for debug - can remove
  static std::string format_str(const Node& nd, const int column_count) {
    std::stringstream ss;
    ss << "Node(pos=" << std::setfill(' ') << std::setw(2) << nd.last_position
      << ", [" << (nd.last_position / column_count)
      << ", " << (nd.last_position % column_count)
      << "], life=" << std::setfill(' ') << std::setw(2) << nd.life_point
      << ", visit=" << nd.visits
      << ", path=" << nd.backtrack << ")";
    return ss.str();
  }
};

int main() {
  int r = input();
  int c = input();
  int n = r * c;
  int begin_pos = 0;
  int end_pos = 0;
  auto pos = [=](int i, int j) { return i * c + j; };

  std::vector<int> cost(n, 0);
  fori(idx, 0, n) {
    switch (cin >> std::ws, input<char>()) {
    case 'S': begin_pos = idx; break;
    case 'E': end_pos = idx; break;
    case 'X': cost[idx] = -1; break;
    case '*': cost[idx] = +1; break;
    default: return 1;
    }
  }

  std::vector<vector<Edge>> edge(n);
  fori(i, 0, r) {
    fori(j, 0, c) {
      if (i + 1 < r) {
        edge[pos(i, j)].emplace_back('D', pos(i + 1, j));
        edge[pos(i + 1, j)].emplace_back('U', pos(i, j));
      }
      if (j + 1 < c) {
        edge[pos(i, j)].emplace_back('R', pos(i, j + 1));
        edge[pos(i, j + 1)].emplace_back('L', pos(i, j));
      }
    }
  }

  std::queue<Node> que;
  que.push(Node(begin_pos, 3, Bits().set(begin_pos), ""));
  auto ans = Node(-1, -1, Bits(), "X");
  while (!que.empty()) {
    const auto node = que.front();
    que.pop();

    bool is_finish = node.last_position == end_pos;
    if (is_finish && node.life_point >= ans.life_point) {
      ans = node;
      std::cerr << "memo answer: " << Node::format_str(ans, r) << '\n';
      continue;
    }

    for (auto nx : edge[node.last_position]) {
      auto node_nx = Node(
        nx.position,
        node.life_point + cost[nx.position],
        Bits(node.visits).set(nx.position),
        node.backtrack + nx.direction
      );
      bool is_never_visited = !node.visits.test(node_nx.last_position);
      bool is_alive = node_nx.life_point > 0;
      if (is_never_visited && is_alive) {
        que.push(node_nx);
      }
    }
  }
  std::cout << ans.life_point << std::endl;
}

auto test_1_in = std::stringstream(R"(
  2 2
  S *
  X E
)");
auto test_1_out = std::stringstream("4");

auto test_2_in = std::stringstream(R"(
3 4
S * * X
X X X X
X * X E
)");
auto test_2_out = std::stringstream("3");

auto test_3_in = std::stringstream(R"(
5 5
S * * * *
X X X X *
* * * * *
* X X X X
* * X * E
)");
auto test_3_out = std::stringstream("16");
