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

auto solve() {
  auto const n = read<int>();
  auto health = read_vec<ll>(n);
  auto const spell = read_vec<ll>(n);
  ll ans = 0;
  ans += std::reduce(std::begin(health), std::end(health), 0ll);
  ans += std::reduce(std::begin(spell), std::end(spell), 0ll);
  ans -= *std::max_element(std::begin(spell), std::end(spell));
  return ans;
}

int main() {
  auto t = read<int>();
  while (t--) {
    std::cout << solve() << std::endl;
  }
}
