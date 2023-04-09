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

ll solve_for(ll x, ll y) {
  slog << "Fuck: " << x << ' ' << y << endl;
  auto other_cost = [&](ll prev, ll len) -> ll {
    if (prev + len > y) {
      return 1e15;
    }
    return len + (y / (prev + len));
  };

  auto cost_to_reach_with_init_len = [&](ll len, bool log = false) {
    auto const other_len = binary_search(0, 1e9 + 1, [&](ll cur_len) {
      return other_cost(len, cur_len) > other_cost(len, cur_len + 1);
    });

    if (log) {
      slog << "here: " << len << ' ' << other_len << ' '
           << other_cost(len, other_len) << endl;
    }

    return other_cost(len, other_len);
  };

  auto cost = [&](ll len, bool log = false) -> ll {
    auto const first = len - 1;
    auto const second = x / len;

    if (len > x) {
      return first + second + 1e15;
    }

    return first + second + cost_to_reach_with_init_len(len, log);
  };

  slog << cost(1, true) << endl;

  auto const len = binary_search(
      1, 1e9 + 1, [&](auto len) { return cost(len) > cost(len + 1); });

  for (ll i = 1; i <= 9; ++i) {
    slog << i << " : " << cost(i) << endl;
  }

  return cost(len, true);
}

auto solve(ll _t) {
  auto const x = read<ll>();
  auto const y = read<ll>();

  return std::min(solve_for(x, y), solve_for(y, x));
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for{2};
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    std::cout << solve(i) << endl;
  }
}
