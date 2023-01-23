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
#include <sstream>
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

bool dfs(ll i, ll s, ll n, std::vector<std::vector<ll>> &dp) {
  if (s < 0)
    return false;
  if (i >= n)
    return dp[i][s] = s == 0;
  if (dp[i][s] != -1)
    return dp[i][s];
  bool ans = false;
  for (ll j = 0; j <= 9; ++j) {
    ans = ans || dfs(i + 1, s - j, n, dp);
  }
  return dp[i][s] = ans;
}

auto solve(ll n, ll s) {
  if (n == 1 && s == 0) {
    std::cout << 0 << ' ' << 0 << std::endl;
    return;
  }
  std::vector dp(n + 1, std::vector(s + 1, -1ll));
  auto is_there = [&] {
    for (ll i = 1; i <= 9; ++i) {
      if (dfs(1, s - i, n, dp)) {
        return true;
      }
    }
    return false;
  };
  if (!is_there()) {
    std::cout << "-1 -1" << std::endl;
    return;
  }
  {
    std::ostringstream res_stream;
    ll cur_sum = s;
    for (ll i = 1; i <= n; ++i) {
      for (ll j = (i == 1 ? 1 : 0); j <= 9; ++j) {
        if (dfs(i, cur_sum - j, n, dp) == 1) {
          res_stream << j;
          cur_sum -= j;
          break;
        }
      }
    }
    auto res = res_stream.str();
    std::cout << res << ' ';
  }
  {
    std::ostringstream res_stream;
    ll cur_sum = s;
    for (ll i = 1; i <= n; ++i) {
      for (ll j = 9; j >= 0; --j) {
        if (dfs(i, cur_sum - j, n, dp) == 1) {
          res_stream << j;
          cur_sum -= j;
          break;
        }
      }
    }
    auto res = res_stream.str();
    std::cout << res << std::endl;
  }
}

int main() {
  auto const m = read<ll>();
  auto const s = read<ll>();
  solve(m, s);
}
