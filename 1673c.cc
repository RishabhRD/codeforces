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

auto make3(ll i, ll j) { return i * 100 + j * 10 + i; }
auto make4(ll i, ll j) { return i * 1000 + j * 100 + j * 10 + i; }
auto make5(ll i, ll j, ll k) {
  return i * 10000 + j * 1000 + k * 100 + j * 10 + i;
}

ll constexpr maximum = 4 * 1e4;
std::vector<ll> make_palindromic_numbers() {
  std::vector<ll> ans{
      1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99,
  };
  auto push_back = [&](ll n) {
    if (n <= maximum)
      ans.push_back(n);
  };
  for (ll i = 1; i <= 9; ++i) {
    for (ll j = 0; j <= 9; ++j) {
      push_back(make3(i, j));
      push_back(make4(i, j));
      for (ll k = 0; k <= 9; ++k) {
        push_back(make5(i, j, k));
      }
    }
  }

  return ans;
}

std::vector<ll> const nums = make_palindromic_numbers();
std::vector dp(maximum + 1, std::vector(nums.size(), -1ll));

ll dfs(ll n, ll i) {
  if (i == nums.size() && n > 0)
    return 0;
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  if (dp[n][i] != -1)
    return dp[n][i];

  return dp[n][i] = (dfs(n - nums[i], i) + dfs(n, i + 1)) % mod;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  std::cout << dfs(n, 0) << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for{0};
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    solve(i);
  }
}
