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

ll mod_power(ll n, ll x, ll mod) {
  if (x == 0)
    return 1;
  auto ans = mod_power(n, x / 2, mod);
  ans = (ans * ans) % mod;
  if (x % 2)
    ans = (ans * n) % mod;
  return ans;
}

ll inv(ll n, ll mod) { return mod_power(n, mod - 2, mod); }

auto binary_search(ll n, ll pos) {
  ll left = 0;
  ll right = n;
  ll small = 0;
  ll large = 0;
  while (left < right) {
    // slog << left << ' ' << right << endl;
    ll const middle = (left + right) / 2;
    if (middle == pos) {
      left = middle + 1;
    } else if (middle < pos) {
      left = middle + 1;
      ++small;
    } else {
      right = middle;
      ++large;
    }
  }
  return std::pair{small, large};
}

auto solve(ll _t) {
  std::vector factorial(1001, 1ll);
  for (ll i = 1; i <= 1000; ++i) {
    factorial[i] = (factorial[i - 1] * i) % mod;
  }
  auto const n = read<ll>();
  auto const x = read<ll>();
  auto const p = read<ll>();

  auto const [nsmall, nlarge] = binary_search(n, p);
  auto const other = n - nsmall - nlarge - 1;
  auto const total_small = x - 1;
  auto const total_large = n - x;

  // slog << nsmall << ' ' << total_small << ' ' << nlarge << ' ' << total_large
  //      << ' ' << other << endl;

  if (nsmall > total_small || nlarge > total_large || other < 0) {
    std::cout << 0 << endl;
    return;
  }

  auto const first =
      (factorial[total_small] * inv(factorial[total_small - nsmall], mod)) %
      mod;
  auto const second =
      (factorial[total_large] * inv(factorial[total_large - nlarge], mod)) %
      mod;
  auto const third = factorial[other];

  std::cout << (((first * second) % mod) * third) % mod << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  // slog << binary_search(std::vector<ll>{1, 3, 5, 2, 5, 6, 7}, 5) << endl;
  solve(0);
}
