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

template <typename T> using matrix_t = std::vector<std::vector<T>>;
template <typename T> using cuboid_t = std::vector<std::vector<std::vector<T>>>;

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

bool dfs(ll e, ll o, ll turn, ll mod, std::vector<cuboid_t<ll>> &dp) {
  if (e == 0 && o == 0) {
    if (turn == 0)
      return mod % 2 == 0;
    else
      return mod % 2 == 1;
  }
  if (dp[e][o][turn][mod] != -1)
    return dp[e][o][turn][mod];
  bool winning = false;
  if (turn == 0) {
    if (mod == 0) {
      if (e > 0 && dfs(e - 1, o, 1, 0, dp) == false)
        winning = true;
      else if (o > 0 && dfs(e, o - 1, 1, 1, dp) == false)
        winning = true;
    } else {
      if (e > 0 && dfs(e - 1, o, 1, 1, dp) == false)
        winning = true;
      else if (o > 0 && dfs(e, o - 1, 1, 0, dp) == false)
        winning = true;
    }
  } else {
    if (e > 0 && dfs(e - 1, o, 0, mod, dp) == false)
      winning = true;
    else if (o > 0 && dfs(e, o - 1, 0, mod, dp) == false)
      winning = true;
  }
  return dp[e][o][turn][mod] = winning;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);

  auto const num_even = std::count_if(std::begin(nums), std::end(nums),
                                      [](auto n) { return n % 2 == 0; });
  auto const num_odd = n - num_even;

  std::vector dp(
      num_even + 1,
      std::vector(num_odd + 1, std::vector(2, std::vector(2, -1ll))));
  if (dfs(num_even, num_odd, 0, 0, dp)) {
    std::cout << "Alice" << endl;
  } else {
    std::cout << "Bob" << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for;
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    solve(i);
  }
}
