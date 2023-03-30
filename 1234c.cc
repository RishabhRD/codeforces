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

bool dfs(ll i, ll j, ll dir, std::vector<std::string> const &grid,
         std::vector<std::vector<std::vector<ll>>> &dp) {
  constexpr static ll horizontal = 0;
  constexpr static ll vertical = 1;
  if (j == grid[0].size())
    return i == 1;

  if (dp[i][j][dir] != -1)
    return dp[i][j][dir];

  bool ans = false;
  if (dir == horizontal) {
    if (grid[i][j] <= '2') {
      ans = dfs(i, j + 1, horizontal, grid, dp);
    } else {
      ans = dfs((i + 1) % 2, j, vertical, grid, dp);
    }
  } else {
    if (grid[i][j] <= '2')
      ans = false;
    else {
      ans = dfs(i, j + 1, horizontal, grid, dp);
    }
  }

  return dp[i][j][dir] = ans;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  std::vector<std::string> grid;
  grid.push_back(read<std::string>());
  grid.push_back(read<std::string>());
  std::vector dp(2, std::vector(n, std::vector(2, -1ll)));
  if (dfs(0, 0, 0, grid, dp)) {
    std::cout << "YES" << endl;
  } else {
    std::cout << "NO" << endl;
  }
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
