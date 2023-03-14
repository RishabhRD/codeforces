#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
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
constexpr char endl = '\n';
template <typename T> using limits = std::numeric_limits<T>;

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

bool log_enabled = false;

class log_t {};

template <typename T> auto operator<<(log_t const &self, T const &ele) {
  if (log_enabled) {
    std::cerr << ele;
  }
  return self;
};

constexpr log_t slog{};

ll dfs(ll i, ll prev, std::vector<std::pair<ll, ll>> const &nums,
       std::vector<std::vector<ll>> &dp) {
  if (i == nums.size()) {
    return 0;
  }

  if (dp[i][prev] != -1)
    return dp[i][prev];

  ll const min = [&]() -> ll {
    if (i == 0)
      return limits<int>::min();
    else if (prev == 0) {
      return nums[i - 1].first;
    } else {
      return nums[i - 1].first + nums[i - 1].second;
    }
  }();

  ll const max = [&]() -> ll {
    if (i == nums.size() - 1) {
      return limits<ll>::max();
    } else {
      return nums[i + 1].first;
    }
  }();

  ll ans = dfs(i + 1, 0, nums, dp);
  if (nums[i].first - nums[i].second > min) {
    ans = std::max(ans, 1 + dfs(i + 1, 0, nums, dp));
  }
  if (nums[i].first + nums[i].second < max) {
    ans = std::max(ans, 1 + dfs(i + 1, 1, nums, dp));
  }

  return dp[i][prev] = ans;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  std::vector<std::pair<ll, ll>> nums;
  for (ll i = 0; i < n; ++i) {
    auto const a = read<ll>();
    auto const b = read<ll>();
    nums.push_back({a, b});
  }

  std::vector dp(n, std::vector<ll>(2, -1ll));
  return std::max(dfs(0, 0, nums, dp), dfs(0, 1, nums, dp));
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << std::endl;
}
