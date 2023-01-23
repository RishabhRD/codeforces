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

auto solve(ll n, std::vector<ll> const &nums, std::vector<ll> const &divisor) {
  safe_map<ll> mp;
  ll cnt = 0;
  std::vector<ll> color;
  for (auto n : nums) {
    auto const group = divisor[n];
    if (!mp[group]) {
      mp[group] = ++cnt;
    }
    color.push_back(mp[group]);
  }
  std::cout << cnt << std::endl;
  for (auto n : color)
    std::cout << n << ' ';
  std::cout << std::endl;
}

int main() {
  std::vector<ll> divisor(1001);
  for (ll i = 2; i <= 1000; ++i) {
    divisor[i] = i;
  }
  for (ll i = 2; i <= 1000; ++i) {
    if (divisor[i] == i) {
      for (ll j = i + i; j <= 1000; j += i) {
        if (divisor[j] == j)
          divisor[j] = i;
      }
    }
  }
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const nums = read_vec<ll>(n);
    solve(n, nums, divisor);
  }
}
