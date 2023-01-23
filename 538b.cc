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

ll dfs(ll n, std::vector<ll> const &binary, std::vector<ll> &next,
       std::vector<ll> &dp) {
  if (n == 0)
    return 0;
  if (dp[n] != -1)
    return dp[n];
  ll min = n;
  for (auto s : binary) {
    if (s <= n) {
      auto const cur = 1 + dfs(n - s, binary, next, dp);
      if (cur <= min) {
        min = cur;
        next[n] = n - s;
      }
    } else {
      break;
    }
  }
  return dp[n] = min;
}

auto solve(ll n, std::vector<ll> const &binary) {
  std::vector<ll> dp(n + 1, -1);
  std::vector<ll> next(n + 1, 1);
  std::cout << dfs(n, binary, next, dp) << std::endl;
  ll cur = n;
  while (cur != 0) {
    auto const right = next[cur];
    std::cout << cur - right << ' ';
    cur = right;
  }
  std::cout << std::endl;
}

int main() {
  std::vector<ll> nums({1});
  for (ll i = 0; i < nums.size(); ++i) {
    auto const first = nums[i] * 10;
    auto const second = first + 1;
    if (first <= 1e6) {
      nums.push_back(first);
    }
    if (second <= 1e6) {
      nums.push_back(second);
    }
  }
  auto const n = read<ll>();
  solve(n, nums);
}
