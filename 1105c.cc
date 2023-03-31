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

ll total_sum(ll i, ll rem, ll n, ll n0, ll n1, ll n2,
             std::vector<std::vector<ll>> &dp) {
  if (i == n) {
    return rem == 0 ? 1 : 0;
  }

  if (dp[i][rem] != -1)
    return dp[i][rem];

  ll ans = 0;

  if (rem == 0) {
    ans = (ans + (n0 * total_sum(i + 1, 0, n, n0, n1, n2, dp)) % mod) % mod;
    ans = (ans + (n1 * total_sum(i + 1, 2, n, n0, n1, n2, dp)) % mod) % mod;
    ans = (ans + (n2 * total_sum(i + 1, 1, n, n0, n1, n2, dp)) % mod) % mod;
  } else if (rem == 1) {
    ans = (ans + (n0 * total_sum(i + 1, 1, n, n0, n1, n2, dp)) % mod) % mod;
    ans = (ans + (n1 * total_sum(i + 1, 0, n, n0, n1, n2, dp)) % mod) % mod;
    ans = (ans + (n2 * total_sum(i + 1, 2, n, n0, n1, n2, dp)) % mod) % mod;
  } else {
    ans = (ans + (n0 * total_sum(i + 1, 2, n, n0, n1, n2, dp)) % mod) % mod;
    ans = (ans + (n1 * total_sum(i + 1, 1, n, n0, n1, n2, dp)) % mod) % mod;
    ans = (ans + (n2 * total_sum(i + 1, 0, n, n0, n1, n2, dp)) % mod) % mod;
  }

  return dp[i][rem] = ans;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const l = read<ll>();
  auto const r = read<ll>();
  auto const [n0, n1, n2] = [l, r] {
    auto const total = (r - l + 1) / 3;
    auto const mod = (r - l + 1) % 3;
    ll n0 = total;
    ll n1 = total;
    ll n2 = total;
    if (l % 3 == 1) {
      if (mod >= 1)
        ++n1;
      if (mod >= 2)
        ++n2;
    } else if (l % 3 == 2) {
      if (mod >= 1)
        ++n2;
      if (mod >= 2)
        ++n0;
    } else {
      if (mod >= 1)
        ++n0;
      if (mod >= 2)
        ++n1;
    }
    return std::tuple{n0, n1, n2};
  }();

  std::vector dp(n, std::vector(3, -1ll));
  std::cout << total_sum(0, 0, n, n0, n1, n2, dp) << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
