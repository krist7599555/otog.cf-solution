// 268 TOI10_map
// https://api.otog.cf/problem/doc/268
// create biggger array as plane, start from center
#include <cstdio>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <queue>
#define loop(i,k,n) for (auto i = (k); i != (n); ++i)

const int MAXN = 200;
const int INVALID = -1;

struct {
  int idx_top = INVALID;
  int idx_left = INVALID;
  int idx_bottom = INVALID;
  int idx_right = INVALID;
} edges[MAXN * MAXN];

int main() {
  int n, m;
  std::scanf("%d %d", &n, &m);
  loop(_, 1, n * m) {
    int idx_a, idx_b;
    char oper;
    scanf("%d %c %d", &idx_a, &oper, &idx_b);
    switch (oper) {
    case 'L':
      edges[idx_a].idx_right = idx_b;
      edges[idx_b].idx_left = idx_a;
      break;
    case 'U':
      edges[idx_a].idx_bottom = idx_b;
      edges[idx_b].idx_top = idx_a;
      break;
    default:
      throw std::runtime_error("invalid operator");
    }
  }

  int ans[2 * n][2 * m]; // double size ans array to store result
  std::fill_n(*ans, 4 * n * m, INVALID);
  struct Data {
    int ans_i, ans_j, id; // ans[ans_i][ans_j] = id
  };

  std::queue<Data> que;
  Data ans_corner = {
    n, // center row ans
    m, // center col ans
    0 // starter_id can be from 0 to n * m
  }; // ans_corner = most top-left corner (also the start point)

  ans[ans_corner.ans_i][ans_corner.ans_j] = ans_corner.id;
  que.push(ans_corner);
  while (!que.empty()) {
    const Data curr = que.front(); que.pop();
    fprintf(stderr, ">> id=%d) x=%d y=%d\n", curr.id, curr.ans_i, curr.ans_j);
    assert(ans[curr.ans_i][curr.ans_j] == curr.id);
    // minimum ans_corner
    if (curr.ans_i < ans_corner.ans_i || curr.ans_j < ans_corner.ans_j) {
      ans_corner = curr;
    }
    // look 4 directions
    for (Data nx : {
      Data { curr.ans_i - 1, curr.ans_j, edges[curr.id].idx_top },
        Data{ curr.ans_i + 1, curr.ans_j, edges[curr.id].idx_bottom },
        Data{ curr.ans_i, curr.ans_j - 1, edges[curr.id].idx_left },
        Data{ curr.ans_i, curr.ans_j + 1, edges[curr.id].idx_right },
    }) {
      if (nx.id != INVALID && ans[nx.ans_i][nx.ans_j] == INVALID) {
        ans[nx.ans_i][nx.ans_j] = nx.id;
        que.push(nx);
      }
    }
  }

  // print ans
  loop(i, ans_corner.ans_i, ans_corner.ans_i + n) {
    loop(j, ans_corner.ans_j, ans_corner.ans_j + m) {
      assert(ans[i][j] != INVALID);
      printf("%d ", ans[i][j]);
    }
    printf("\n");
  }
}
