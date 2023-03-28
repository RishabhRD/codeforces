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

ll rev_prod(ll i, ll j, std::vector<ll> const &a, std::vector<ll> const &b,
            std::vector<std::vector<ll>> &dp) {
  if (i == j) {
    return dp[i][j] = a[i] * b[j];
  } else if (j - i == 1) {
    return dp[i][j] = a[i] * b[j] + b[i] * a[j];
  }

  if (dp[i][j] != -1)
    return dp[i][j];

  return dp[i][j] =
             a[i] * b[j] + b[i] * a[j] + rev_prod(i + 1, j - 1, a, b, dp);
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const a = read_vec<ll>(n);
  auto const b = read_vec<ll>(n);

  std::vector<ll> prefix_sum(n);
  prefix_sum[0] = a[0] * b[0];
  for (ll i = 1; i < n; ++i) {
    prefix_sum[i] = a[i] * b[i] + prefix_sum[i - 1];
  }
  auto const get_sum = [&](ll i, ll j) {
    if (i > j)
      return 0ll;
    if (i == 0)
      return prefix_sum[j];
    return prefix_sum[j] - prefix_sum[i - 1];
  };

  ll max_sum = 0;
  std::vector dp(n, std::vector(n, -1ll));
  for (ll i = 0; i < n; ++i) {
    for (ll j = i; j < n; ++j) {
      max_sum = std::max(max_sum, get_sum(0, i - 1) + get_sum(j + 1, n - 1) +
                                      rev_prod(i, j, a, b, dp));
    }
  }
  std::cout << max_sum << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
