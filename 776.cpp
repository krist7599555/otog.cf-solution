// 776
// https://api.otog.cf/problem/doc/766
// precompute dijktra across middle point of each graph query
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <tuple>
#include <map>
#include <climits>
#define loop(i,n) for(int i = 0; i != n; ++i)
using namespace std;
typedef std::vector<int> Vec;

inline int input() {
  int tmp; std::cin >> tmp; return tmp;
}

struct Edge {
  int node;
  int weight;
  Edge(int node, int weight): node(node), weight(weight) {}
  friend bool operator>(const Edge& a, const Edge& b) {
    return a.weight > b.weight;
  }
};

Vec shortest_path(int start, const std::vector<std::vector<Edge>>& graph) {
  std::vector<int> result(graph.size(), INT_MAX);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

  pq.emplace(start, result[start] = 0);
  while (!pq.empty()) {
    int node = pq.top().node;
    int weight = pq.top().weight;
    pq.pop();
    if (result[node] == weight) {
      for (Edge nx : graph[node]) {
        if (weight + nx.weight < result[nx.node]) {
          pq.emplace(nx.node, result[nx.node] = weight + nx.weight);
        }
      }
    }
  }
  return result;
}

int main() {
  int n = input();
  int edge_count = input();
  int food_count = input();
  int question_count = input();

  std::vector<std::vector<Edge>> graph(n);
  loop(_, edge_count) {
    int u = input();
    int v = input();
    int w = input();
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  std::map<int, Vec> shortest_paths;
  loop(_, food_count) {
    int food_location = input();
    shortest_paths[food_location] = shortest_path(food_location, graph);
  }

  loop(_, question_count) {
    int begin_loc = input();
    int food_loc = input();
    int end_loc = input();
    std::cout << shortest_paths[food_loc][begin_loc] + shortest_paths[food_loc][end_loc] << '\n';
  }
}
