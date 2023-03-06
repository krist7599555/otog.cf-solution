// https://api.otog.cf/problem/doc/720
// binarysearch
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
typedef std::string str;
#define rep(i, k, n) for (auto i = k; i != n; ++i)
#define loop(var, n) rep(var, 0, n)
#define all(a) a.begin(), a.end()
const int INF = 1e9;

struct Edge {
  int to;
  int weight;
  friend bool operator>(const Edge& a, const Edge& b) {
    return a.weight > b.weight;
  }
};
struct Node {
  int time;
  std::vector<Edge> edges;
};

template<typename T = int>
inline T input() { T tmp; std::cin >> tmp; return tmp; }

struct Walk: public std::tuple<int, int, int> {
  int time() const { return std::get<0>(*this); }
  int fuel() const { return std::get<1>(*this); }
  int id() const { return std::get<2>(*this); }
  Walk(int time, int fuel, int id): std::tuple<int, int, int>(time, fuel, id) {}
};

int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(0);
  int node_count = input();
  int edge_count = input();

  str start_node = input<str>();
  str end_node = input<str>();
  int max_fuel = input();

  std::vector<Node> graph(node_count);
  std::unordered_map<str, int> id2idx;

  rep(idx, 0, node_count) {
    str id = input<str>();
    int time = input();
    id2idx[id] = idx;
    graph[idx] = Node{ time, {} };
  }
  loop(_, edge_count) {
    int u = id2idx.at(input<str>());
    int v = id2idx.at(input<str>());
    int weight = input();
    graph[u].edges.push_back({ v, weight });
    graph[v].edges.push_back({ u, weight });
  }

  int start_i = id2idx.at(start_node);
  int end_i = id2idx.at(end_node);


#define SOLUTION_2

#ifdef SOLUTION_1
  // use dijktra sort by .time (to gurantee answer minimum time)
  // but valid state is check on .fuel
  std::vector<Walk> dijkstra(node_count, Walk{ INF, INF, INF }); // maintain minium .fuel
  std::priority_queue<Walk, std::vector<Walk>, std::greater<Walk>> pq; // maintain minimum .time
  pq.push(dijkstra[start_i] = Walk{ 0, 0, start_i });
  while (!pq.empty()) {
    Walk curr = pq.top();
    pq.pop();
    if (curr.id() == end_i) break;
    if (dijkstra[curr.id()].fuel() == curr.fuel()) {
      for (const Edge& nx : graph[curr.id()].edges) {
        auto nxt = Walk{
          std::max(curr.time(), graph[nx.to].time),
          curr.fuel() + nx.weight,
          nx.to
        };
        if (nxt.fuel() < dijkstra[nx.to].fuel() && nxt.fuel() <= max_fuel) {
          pq.push(dijkstra[nx.to] = nxt);
        }
      }
    }
  }
  auto ans = dijkstra[end_i];
  printf("%d %d\n", ans.time(), ans.fuel());
#endif

#ifdef SOLUTION_2
  /// binary search on .time
  auto calculate_fuel_used_dijkstra = [](const std::vector<Node>& graph, int start_node, int end_node, int max_time) {
    std::vector<int> dp(graph.size(), INF); // fuel
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    pq.push(Edge{ start_node, dp[start_node] = 0 });
    while (!pq.empty()) {
      Edge curr = pq.top();
      pq.pop();
      if (dp[curr.to] == curr.weight) {
        // printf(" node %d use fuel %d\n", curr.to, curr.weight);
        for (const Edge& nx : graph[curr.to].edges) {
          if (graph[nx.to].time <= max_time && curr.weight + nx.weight < dp[nx.to]) {
            pq.push(Edge{ nx.to, dp[nx.to] = curr.weight + nx.weight });
          }
        }
      }
    }
    return dp[end_node];
  };


  std::vector<int> times;
  std::transform(all(graph), std::back_inserter(times), [](const Node& node) { return node.time; });
  std::sort(all(times));
  auto ans_time = *std::lower_bound(all(times), -1, [&](int time, int _) {
    return !(calculate_fuel_used_dijkstra(graph, start_i, end_i, time) <= max_fuel);
    });
  printf("%d %d\n", ans_time, calculate_fuel_used_dijkstra(graph, start_i, end_i, ans_time));
#endif
}
