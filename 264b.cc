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

template <typename Container, typename Comparator = std::less<>>
auto make_sorted(Container vec, Comparator &&cmp = std::less<>{}) {
  std::sort(std::begin(vec), std::end(vec), cmp);
  return vec;
}

template <typename Container> auto make_reversed(Container vec) {
  std::reverse(std::begin(vec), std::end(vec));
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

// If there is an edge between b and c, then there shuould not be an edge
// between a and c, but there should be an edge between a and b (if possible)

ll dfs(ll i, std::vector<std::vector<ll>> &graph, std::vector<ll> &dp) {
  if (dp[i] != -1)
    return dp[i];

  ll ans = 0;
  for (auto n : graph[i]) {
    ans = std::max(ans, dfs(n, graph, dp));
  }

  return dp[i] = 1 + ans;
}

auto solve(ll _t) {
  std::vector<std::vector<ll>> prime_factors(1e5 + 1);
  for (ll i = 2; i <= 1e5; ++i) {
    if (prime_factors[i].empty()) {
      for (ll j = i; j <= 1e5; j += i) {
        prime_factors[j].push_back(i);
      }
    }
  }
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);

  std::vector<std::vector<ll>> graph(n);
  std::vector<ll> min_val_prime_factor(1e5 + 1, n);
  for (ll i = n - 1; i >= 0; --i) {
    for (auto k : prime_factors[nums[i]]) {
      if (min_val_prime_factor[k] < n) {
        graph[i].push_back(min_val_prime_factor[k]);
      }
    }
    for (auto k : prime_factors[nums[i]]) {
      min_val_prime_factor[k] = i;
    }
  }

  ll max = 0;
  std::vector dp(n, -1ll);
  for (ll i = 0; i < n; ++i) {
    max = std::max(max, dfs(i, graph, dp));
  }
  return max;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << endl;
}
