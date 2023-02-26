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

ll dfs(ll n, ll cur, std::vector<std::vector<ll>> &dp) {
  if (n == 0) {
    if (cur == 3)
      return 1;
    else
      return 0;
  }
  if (dp[n][cur] != -1)
    return dp[n][cur];
  ll ans = 0;
  for (ll i = 0; i < 4; ++i) {
    if (i != cur) {
      ans = (ans + dfs(n - 1, i, dp)) % mod;
    }
  }
  return dp[n][cur] = ans;
}

ll mod_add(ll a, ll b) { return (a + b) % mod; }

ll num_ways(ll src, ll dest, ll n,
            std::vector<std::vector<std::unordered_map<ll, ll>>> &dp) {
  if (n == 0) {
    if (src == dest)
      return 1;
    else
      return 0;
  }
  if (n == 1) {
    return src == dest ? 0 : 1;
  }
  if (dp[src][dest].count(n)) {
    return dp[src][dest][n];
  }
  ll const n1 = n / 2;
  ll const n2 = n - n1;
  ll const first = (num_ways(src, 0, n1, dp) * num_ways(0, dest, n2, dp)) % mod;
  ll const second =
      (num_ways(src, 1, n1, dp) * num_ways(1, dest, n2, dp)) % mod;
  ll const third = (num_ways(src, 2, n1, dp) * num_ways(2, dest, n2, dp)) % mod;
  ll const fourth =
      (num_ways(src, 3, n1, dp) * num_ways(3, dest, n2, dp)) % mod;
  return dp[src][dest][n] =
             mod_add(mod_add(mod_add(first, second), third), fourth);
}

int main() {
  auto const n = read<ll>();
  std::vector dp(4, std::vector(4, std::unordered_map<ll, ll>()));
  std::cout << num_ways(0, 0, n, dp) << std::endl;
}
