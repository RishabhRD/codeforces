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
template <typename T> using matrix_t = std::vector<std::vector<T>>;
template <typename T> using cuboid_t = std::vector<std::vector<std::vector<T>>>;
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

ll dfs(ll i, ll cur_mod, ll is_first, std::string_view str, cuboid_t<ll> &dp) {
  if (i == str.size()) {
    if (cur_mod == 0 && is_first == 0)
      return 1;
    return 0;
  }

  if (dp[i][cur_mod][is_first] != -1)
    return dp[i][cur_mod][is_first];

  ll ans = -1;
  if (is_first == 1) {
    if (str[i] == '0')
      ans = std::max(ans, 1 + dfs(i + 1, 0, 1, str, dp));
    else {
      ll const new_mod = (cur_mod + (str[i] - '0')) % 3;
      ans = std::max({
          ans,
          dfs(i + 1, new_mod, 0, str, dp),
          (new_mod == 0 ? 1 : 0) + dfs(i + 1, 0, 1, str, dp),
      });
    }
  } else {
    ll const new_mod = (cur_mod + (str[i] - '0')) % 3;
    ans = std::max({
        ans,
        dfs(i + 1, new_mod, 0, str, dp),
        (new_mod == 0 ? 1 : 0) + dfs(i + 1, 0, 1, str, dp),
    });
  }
  return dp[i][cur_mod][is_first] = ans;
}

auto solve(ll _t) {
  auto const str = read<std::string>();
  ll const n = str.size();
  cuboid_t<ll> dp(n, std::vector(3, std::vector(2, -1ll)));
  std::cout << dfs(0, 0, 1, str, dp) << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
