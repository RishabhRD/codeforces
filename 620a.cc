#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
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

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

using ll = long long;
constexpr ll mod = 1e9 + 7;

using safe_set = std::unordered_set<ll, custom_hash>;

template <typename T> using safe_map = std::unordered_map<ll, T>;

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

template <typename T> auto read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

auto solve() {}

int main() {
  auto const x1 = read<ll>();
  auto const y1 = read<ll>();
  auto const x2 = read<ll>();
  auto const y2 = read<ll>();
  auto const dx = std::abs(x2 - x1);
  auto const dy = std::abs(y2 - y1);
  auto const step = std::min(dx, dy);
  auto const sigx = x2 - x1;
  auto const sigy = y2 - y1;
  ll newx = x1;
  if (sigx < 0) {
    newx -= step;
  } else {
    newx += step;
  }
  ll newy = y1;
  if (sigy < 0) {
    newy -= step;
  } else {
    newy += step;
  }
  std::cout << step + std::abs(x2 - newx) + std::abs(y2 - newy) << std::endl;
}
