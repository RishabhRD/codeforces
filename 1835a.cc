// codeforces template  {{{
// vim: foldmethod=marker
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
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ll = long long;

// hashing {{{
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

using safe_set = std::unordered_set<ll, custom_hash>;

template <typename T> using safe_map = std::unordered_map<ll, T>;
// }}}

// ModInt {{{
namespace ModInt {
template <ll mod> class mod_int_t {
public:
  ll n;

  constexpr mod_int_t(ll n_arg = 0) noexcept : n((n_arg + mod) % mod) {}

  constexpr mod_int_t power(ll x) const noexcept {
    if (x == 0)
      return 1;
    auto ans = power(x / 2);
    ans.n = (ans.n * ans.n) % mod;
    if (x % 2)
      ans.n = (ans.n * n) % mod;
    return ans;
  }

  constexpr mod_int_t inv() const noexcept { return power(mod - 2); }
};

template <ll mod>
constexpr mod_int_t<mod> &operator++(mod_int_t<mod> &a) noexcept {
  a.n = (a.n + 1) % mod;
  return a;
}

template <ll mod>
constexpr mod_int_t<mod> operator++(mod_int_t<mod> &a, int) noexcept {
  auto ans = a;
  a.n = (a.n + 1) % mod;
  return ans;
}

template <ll mod>
constexpr mod_int_t<mod> &operator--(mod_int_t<mod> &a) noexcept {
  a.n = (a.n - 1 + mod) % mod;
  return a;
}

template <ll mod>
constexpr mod_int_t<mod> operator--(mod_int_t<mod> &a, int) noexcept {
  auto ans = a;
  a.n = (a.n - 1 + mod) % mod;
  return ans;
}

template <ll mod>
constexpr mod_int_t<mod> operator+(mod_int_t<mod> a,
                                   mod_int_t<mod> b) noexcept {
  return (a.n + b.n) % mod;
}

template <ll mod>
constexpr mod_int_t<mod> &operator+=(mod_int_t<mod> &a,
                                     mod_int_t<mod> b) noexcept {
  a = a + b;
  return a;
}

template <ll mod>
constexpr mod_int_t<mod> operator-(mod_int_t<mod> a,
                                   mod_int_t<mod> b) noexcept {
  return (a.n - b.n + mod) % mod;
}

template <ll mod>
constexpr mod_int_t<mod> &operator-=(mod_int_t<mod> &a,
                                     mod_int_t<mod> b) noexcept {
  a = a - b;
  return a;
}

template <ll mod>
constexpr mod_int_t<mod> operator*(mod_int_t<mod> a,
                                   mod_int_t<mod> b) noexcept {
  return (a.n * b.n) % mod;
}

template <ll mod>
constexpr mod_int_t<mod> &operator*=(mod_int_t<mod> &a,
                                     mod_int_t<mod> b) noexcept {
  a = a * b;
  return a;
}

template <ll mod>
constexpr mod_int_t<mod> operator/(mod_int_t<mod> a,
                                   mod_int_t<mod> b) noexcept {
  return a * b.inv();
}

template <ll mod>
constexpr mod_int_t<mod> &operator/=(mod_int_t<mod> &a,
                                     mod_int_t<mod> b) noexcept {
  a = a / b;
  return a;
}

template <ll mod>
constexpr std::ostream &operator<<(std::ostream &os,
                                   mod_int_t<mod> b) noexcept {
  os << b.n;
  return os;
}

template <ll mod>
constexpr std::istream &operator>>(std::istream &in,
                                   mod_int_t<mod> &b) noexcept {
  in >> b.n;
  b.n = (b.n + mod) % mod;
  return in;
}
} // namespace ModInt
// }}}

constexpr char endl = '\n';
// IO {{{
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

auto operator<<(log_t const &self, std::ostream &(*f)(std::ostream &)) {
  if (log_enabled) {
    std::cerr << f;
  }
  return self;
};

constexpr log_t slog{};
// }}}

// codeforces template }}}

constexpr ll mod = 1e9 + 7;
using mii = ModInt::mod_int_t<mod>;

auto ten_e(ll n) {
  ll cur = 1;
  for (ll i = 0; i < n; ++i) {
    cur *= 10;
  }
  return cur;
}

auto solve(ll _t) {
  auto const A = read<ll>();
  auto const B = read<ll>();
  auto const C = read<ll>();
  auto k = read<ll>();

  for (ll a = ten_e(A - 1); a < ten_e(A); ++a) {
    auto const left_b = std::max(ten_e(C - 1) - a, ten_e(B - 1));
    auto const right_b = std::min(ten_e(C) - a, ten_e(B));
    auto const n_ele = right_b - left_b;
    if (n_ele <= 0)
      continue;

    if (n_ele >= k) {
      ll const b = left_b + k - 1;
      ll const c = a + b;
      std::cout << a << " + " << b << " = " << c << std::endl;
      return;
    }
    k -= n_ele;
  }

  std::cout << -1 << std::endl;
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
