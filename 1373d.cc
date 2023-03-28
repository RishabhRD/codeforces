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

bool log_enabled = true;

class log_t {};

template <typename T> auto operator<<(log_t const &self, T const &ele) {
  if (log_enabled) {
    std::cerr << ele;
  }
  return self;
};

constexpr log_t slog{};

// state
// 0 : starting
// 1 : reversing, started from even
// 2 : reversing, started from odd
// 3 : done

ll dfs(ll i, ll state, std::vector<ll> const &nums,
       std::vector<std::vector<std::optional<ll>>> &dp) {
  ll const n = nums.size();
  if (i == nums.size()) {
    if ((state == 1 && n % 2 == 1) || (state == 2 && n % 2 == 0))
      return limits<ll>::min();
    else
      return 0;
  }
  if (dp[i][state].has_value())
    return dp[i][state].value();
  ll ans = 0;
  if (state == 0) {
    ans = std::max(ans,
                   ((i % 2 == 0) ? nums[i] : 0) + dfs(i + 1, state, nums, dp));
    ll const next_state = (i % 2 == 0) ? 1 : 2;
    ans = std::max(ans, dfs(i, next_state, nums, dp));
  } else if (state == 1) {
    ans = std::max(ans,
                   ((i % 2 == 1) ? nums[i] : 0) + dfs(i + 1, state, nums, dp));
    if (i % 2 == 1)
      ans =
          std::max(ans, ((i % 2 == 1) ? nums[i] : 0) + dfs(i + 1, 3, nums, dp));
  } else if (state == 2) {
    ans = std::max(ans,
                   ((i % 2 == 1) ? nums[i] : 0) + dfs(i + 1, state, nums, dp));
    if (i % 2 == 0)
      ans = std::max(ans, dfs(i + 1, 3, nums, dp));
  } else {
    ans = std::max(ans,
                   ((i % 2 == 0) ? nums[i] : 0) + dfs(i + 1, state, nums, dp));
  }
  // slog << i << ' ' << state << ' ' << ans << endl;
  dp[i][state] = ans;
  return dp[i][state].value();
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  std::vector dp(n, std::vector(4, std::optional<ll>{}));
  std::cout << dfs(0, 0, nums, dp) << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for{4};
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    solve(i);
  }
}
