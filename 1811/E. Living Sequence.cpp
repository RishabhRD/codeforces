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
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
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

template <typename Predicate>
ll binary_search(ll low, ll high, Predicate &&predicate) {
  if (low >= high)
    return low;
  auto const mid = low + (high - low) / 2;
  if (predicate(mid)) {
    return binary_search(mid + 1, high, predicate);
  } else {
    return binary_search(low, mid, predicate);
  }
}

ll dfs(ll i, ll is_first, ll is_tight, std::string_view str, cuboid_t<ll> &dp) {
  if (i >= str.size())
    return 1;
  if (dp[i][is_first][is_tight] != -1)
    return dp[i][is_first][is_tight];
  ll ans = 0;
  if (is_first) {
    if (is_tight) {
      ll cnt = (str[i] - '0') - 1;
      if (str[i] > '4')
        --cnt;
      ans += cnt * dfs(i + 1, 0, 0, str, dp);
      if (str[i] != '4')
        ans += dfs(i + 1, 0, 1, str, dp);
    } else {
      ans += 8 * dfs(i + 1, 0, 0, str, dp);
    }
    ans += dfs(i + 1, 1, 0, str, dp);
  } else {
    if (is_tight) {
      ll cnt = (str[i] - '0');
      if (str[i] > '4')
        --cnt;
      ans += cnt * dfs(i + 1, 0, 0, str, dp);
      if (str[i] != '4')
        ans += dfs(i + 1, 0, 1, str, dp);
    } else {
      ans += 9 * dfs(i + 1, 0, 0, str, dp);
    }
  }
  return dp[i][is_first][is_tight] = ans;
}

std::unordered_map<ll, ll> mp;

auto solve(ll _t) {
  auto const k = read<ll>();
  auto count = [&](auto n) {
    if (mp.count(n))
      return mp[n];
    std::ostringstream os;
    os << n;
    auto const str = os.str();
    std::vector dp(str.size(), std::vector(2, std::vector(2, -1ll)));
    return mp[n] = dfs(0, 1, 1, str, dp) - 2;
  };

  std::cout << binary_search(1, 1e15 + 1, [&](auto n) {
    return count(n) < k - 1;
  }) << endl;
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
