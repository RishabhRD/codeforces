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

template <typename Predicate>
ll binary_search(ll low, ll high, Predicate &&predicate) {
  if (low >= high)
    return low;
  auto const mid = low + (high - low) / 2;
  if (predicate(mid)) {
    return binary_search(mid + 1, high, predicate);
  } else {
    return binary_search(low, mid, predicate);
  }
}

int main() {
  auto const N = read<ll>();
  auto const M = read<ll>();
  auto const d = read<ll>();
  auto const n = N * M;
  auto nums = read_vec<ll>(n);
  if (n == 1) {
    std::cout << 0 << std::endl;
    return 0;
  }
  safe_set mods;
  for (auto n : nums) {
    mods.insert(n % d);
  }
  if (mods.size() != 1) {
    std::cout << -1 << std::endl;
    return 0;
  }
  std::vector<ll> arr;
  auto const mod = *mods.begin();
  for (ll i = 1; i <= 1e4; ++i) {
    if (i % d == mod) {
      arr.push_back(i);
    }
  }
  auto steps = [&](auto e) {
    ll sum = 0;
    for (auto n : nums) {
      auto const diff = std::abs(n - e);
      sum += diff / d;
    }
    return sum;
  };
  auto const idx = binary_search(0, arr.size() - 1, [&](auto i) {
    return steps(arr[i]) > steps(arr[i + 1]);
  });
  std::cout << steps(arr[idx]) << std::endl;
}
