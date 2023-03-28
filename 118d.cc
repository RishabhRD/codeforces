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
constexpr ll mod = 1e8;
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

ll num_comb(ll i, ll j, ll turn, ll k1, ll k2, ll n1, ll n2,
            std::vector<std::vector<std::vector<ll>>> &dp) {
  if (i > n1 || j > n2) {
    return 0;
  }
  if (i == n1 && j == n2)
    return 1;
  if (dp[i][j][turn] != -1)
    return dp[i][j][turn];

  ll sum = 0;
  if (turn == 0) {
    for (ll k = 1; k <= k1; ++k) {
      sum = (sum + num_comb(i + k, j, 1, k1, k2, n1, n2, dp)) % mod;
    }
  } else {
    for (ll k = 1; k <= k2; ++k) {
      sum = (sum + num_comb(i, j + k, 0, k1, k2, n1, n2, dp)) % mod;
    }
  }

  return dp[i][j][turn] = sum;
}

auto solve(ll _t) {
  auto const n1 = read<ll>();
  auto const n2 = read<ll>();
  auto const k1 = read<ll>();
  auto const k2 = read<ll>();

  std::vector dp(n1 + 1, std::vector(n2 + 1, std::vector(2, -1ll)));

  return (num_comb(0, 0, 0, k1, k2, n1, n2, dp) +
          num_comb(0, 0, 1, k1, k2, n1, n2, dp)) %
         mod;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << endl;
}
