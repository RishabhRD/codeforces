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

ll dfs(ll i, ll state, std::vector<ll> const &a, std::vector<ll> const &b,
       std::vector<std::vector<ll>> &dp) {
  if (i >= a.size())
    return 0;
  if (dp[i][state] != -1)
    return dp[i][state];
  if (state == 0) {
    return dp[i][state] = std::max({
               dfs(i + 1, 0, a, b, dp),
               a[i] + dfs(i + 1, 1, a, b, dp),
               b[i] + dfs(i + 1, 2, a, b, dp),
           });
  } else if (state == 1) {
    return dp[i][state] = std::max(dfs(i + 1, 0, a, b, dp),
                                   b[i] + dfs(i + 1, 2, a, b, dp));
  } else {
    return dp[i][state] = std::max(dfs(i + 1, 0, a, b, dp),
                                   a[i] + dfs(i + 1, 1, a, b, dp));
  }
}

auto solve(ll n, std::vector<ll> const &a, std::vector<ll> const &b) {
  std::vector dp(n, std::vector(3, -1ll));
  return dfs(0, 0, a, b, dp);
}

int main() {
  auto const n = read<ll>();
  auto const a = read_vec<ll>(n);
  auto const b = read_vec<ll>(n);
  std::cout << solve(n, a, b) << std::endl;
}
