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

constexpr ll min_inf = -(1e13);

ll max_health(ll i, ll n, std::vector<ll> const &nums,
              std::vector<std::vector<std::optional<ll>>> &dp) {
  if (n < 0)
    return min_inf;
  if (n > i + 1) {
    return min_inf;
  }
  if (i < 0 && n == 0)
    return 0;

  if (dp[i][n].has_value())
    return dp[i][n].value();

  ll ans = max_health(i - 1, n, nums, dp);
  ll const other = nums[i] + max_health(i - 1, n - 1, nums, dp);
  if (other >= 0) {
    ans = std::max(ans, other);
  }

  dp[i][n] = ans;
  return dp[i][n].value();
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  std::vector dp(n + 1, std::vector(n + 1, std::optional<ll>{}));
  for (ll i = n; i >= 0; --i) {
    if (max_health(n - 1, i, nums, dp) >= 0) {
      return i;
    }
  }
  return 0ll;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << endl;
}
