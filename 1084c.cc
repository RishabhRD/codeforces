using ll = long long;

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

template <typename Iter> struct range_of {
  range_of(Iter begin, Iter end) : _begin(begin), _end(end) {}
  Iter begin() const noexcept { return _begin; }
  Iter end() const noexcept { return _end; }

private:
  Iter _begin;
  Iter _end;
};

template <typename Iter> range_of(Iter, Iter) -> range_of<Iter>;

template <typename Container, typename Comparator = std::less<>>
auto make_sorted(Container vec, Comparator &&cmp = std::less<>{}) {
  std::sort(std::begin(vec), std::end(vec), cmp);
  return vec;
}

template <typename Container> auto make_reversed(Container vec) {
  std::reverse(std::begin(vec), std::end(vec));
  return vec;
}

// codeforces template }}}

constexpr ll mod = 1e9 + 7;
using mii = ModInt::mod_int_t<mod>;

// group by {{{
namespace GroupBy {
template <typename Iter, typename F> class group_by_iterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = range_of<Iter>;

  group_by_iterator(Iter begin, Iter end, F f) : begin(begin), end(end), f(f) {}

  value_type operator*() const { return {begin, compute_end()}; }

  group_by_iterator &operator++() {
    begin = compute_end();
    cached_end = std::nullopt;
    return *this;
  }

  group_by_iterator operator++(int) const {
    auto cur = *this;
    begin = compute_end();
    cached_end = std::nullopt;
    return cur;
  }

  bool operator==(group_by_iterator const &other) const {
    return begin == other.begin && end == other.end;
  }

private:
  Iter compute_end() const {
    if (cached_end.has_value())
      return cached_end.value();
    if (begin == end) {
      return end;
    }
    Iter prev = begin;
    Iter cur = std::next(prev);
    while (cur != end) {
      if (f(*prev, *cur)) {
        prev = cur;
        ++cur;
      } else {
        break;
      }
    }
    cached_end = cur;
    return cur;
  }

  Iter begin;
  Iter end;
  mutable std::optional<Iter> cached_end;
  F f;
};
} // namespace GroupBy

template <typename Iter, typename F>
auto group_by(Iter begin, Iter end, F &&f) {
  using namespace GroupBy;
  return range_of{group_by_iterator<Iter, F>{begin, end, f},
                  group_by_iterator<Iter, F>{end, end, f}};
}

template <typename Range, typename F> auto group_by(Range &&rng, F &&f) {
  using namespace GroupBy;
  using Iter = typename std::remove_reference_t<Range>::iterator;
  return range_of{group_by_iterator<Iter, F>{std::begin(rng), std::end(rng), f},
                  group_by_iterator<Iter, F>{std::end(rng), std::end(rng), f}};
}
// group by }}}

auto solve(ll _t) {
  auto const _str = read<std::string>();
  std::string str;
  std::copy_if(std::begin(_str), std::end(_str), std::back_inserter(str),
               [](auto c) { return c == 'a' || c == 'b'; });
  auto const n = str.size();

  mii ans{1};
  for (auto rng : group_by(str, std::equal_to<>{})) {
    if (*rng.begin() == 'a') {
      ans *= mii{rng.end() - rng.begin() + 1};
    }
  }
  std::cout << ans - mii{1} << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
