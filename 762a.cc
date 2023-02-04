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
  auto const n = read<ll>();
  auto const k = read<ll>();
  std::vector<ll> pre_divisors;
  std::vector<ll> post_divisors;
  for (ll i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      auto const first = i;
      auto const second = n / i;
      pre_divisors.push_back(first);
      if (first != second)
        post_divisors.push_back(second);
    }
  }
  std::reverse(std::begin(post_divisors), std::end(post_divisors));
  auto const n1 = pre_divisors.size();
  auto const n2 = post_divisors.size();
  if (n1 + n2 < k)
    std::cout << -1 << std::endl;
  else {
    if (k <= n1) {
      std::cout << pre_divisors[k - 1] << std::endl;
    } else {
      std::cout << post_divisors[k - n1 - 1] << std::endl;
    }
  }
}
