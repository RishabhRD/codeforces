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
  // for (ll i = 0; i <= 100; ++i) {
  //   std::cerr << (i * (i + 1)) / 2 << ' ' << ((i * (i + 1)) / 2) % 6
  //             << std::endl;
  // }
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const x = read<ll>();
    auto const p = read<ll>();
    auto const req = (0 - x + n) % n;
    std::vector<ll> res;
    for (ll i = 1; i <= std::min(p, 10 * n); ++i) {
      auto const k = (i * (i + 1)) / 2;
      res.push_back(k % n);
      // std::cerr << "( " << k % n << " ) " << ' ';
    }
    // std::cerr << std::endl;
    if (std::find(std::begin(res), std::end(res), req) == std::end(res)) {
      std::cout << "No" << std::endl;
    } else {
      std::cout << "Yes" << std::endl;
    }
  }
}
