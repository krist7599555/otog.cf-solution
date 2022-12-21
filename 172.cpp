#include <iostream>
using namespace std;
int main() {
  int n, m;
  int arr[20][20];
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> arr[i][j];
      arr[i][j] += max(
        i > 0 ? arr[i - 1][j] : 0,
        j > 0 ? arr[i][j - 1] : 0
      );
    }
  }
  std::cout << arr[n - 1][m - 1];
}
