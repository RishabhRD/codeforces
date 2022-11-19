#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T> T read() {
  T t;
  std::cin >> t;
  return t;
}

template <typename T> std::vector<T> read_vec(int n) {
  std::vector<T> vec(n);
  for (auto &ele : vec)
    std::cin >> ele;
  return vec;
}

template <typename T> std::vector<T> read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

using ll = long long;

ll solve(int l, int r, int x, int a, int b, int calls) {
  if (calls > 3)
    return INT32_MAX;
  if (a == b)
    return 0;
  if (std::abs(b - a) >= x) {
    return 1;
  }
  ll ansLeft = INT32_MAX;
  if (b - l >= x) {
    ansLeft = 1 + solve(l, r, x, a, l, calls + 1);
  }
  ll ansRight = INT32_MAX;
  if (r - b >= x) {
    ansRight = 1 + solve(l, r, x, a, r, calls + 1);
  }
  return std::min(ansLeft, ansRight);
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const l = read<int>();
    auto const r = read<int>();
    auto const x = read<int>();
    auto const a = read<int>();
    auto const b = read<int>();
    auto const ans = solve(l, r, x, a, b, 0);
    if (ans >= INT32_MAX) {
      std::cout << -1 << std::endl;
    } else {
      std::cout << ans << std::endl;
    }
  }
}
