// codeforces template  {{{
// vim: foldmethod=marker
#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <functional>
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
template <typename T> using limits = std::numeric_limits<T>;

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

namespace rng = std::ranges; // NOLINT
namespace vw = std::views;   // NOLINT

template <typename T> struct cast_to {
  auto operator()(auto &&e) { return static_cast<T>(e); }
};

// functional {{{
namespace rd {
#define lift(func)                                                             \
  [](auto &&...args) noexcept(noexcept(func(std::forward<decltype(args)>(      \
      args)...))) -> decltype(func(std::forward<decltype(args)>(args)...)) {   \
    return func(std::forward<decltype(args)>(args)...);                        \
  }
template <class F, class... Args>
constexpr auto bind_back(F &&f, Args &&...args) {
  return [ f_ = std::forward<F>(f),
           ... args_ = std::forward<Args>(args) ](auto &&...other_args)
    requires std::invocable<F &, decltype(other_args)..., Args &...>
  {
    return std::invoke(f_, std::forward<decltype(other_args)>(other_args)...,
                       args_...);
  };
}
} // namespace rd

namespace rd {
template <class F, class G> struct compose_fn {
  [[no_unique_address]] F f;
  [[no_unique_address]] G g;

  template <class A, class B>
  compose_fn(A &&a, B &&b) : f(std::forward<A>(a)), g(std::forward<B>(b)) {}

  template <class A, class B, class... Args>
  static constexpr auto call(A &&a, B &&b, Args &&...args) {
    if constexpr (std::is_void_v<std::invoke_result_t<G, Args...>>) {
      std::invoke(std::forward<B>(b), std::forward<Args>(args)...);
      return std::invoke(std::forward<A>(a));
    } else {
      return std::invoke(
          std::forward<A>(a),
          std::invoke(std::forward<B>(b), std::forward<Args>(args)...));
    }
  }

  template <class... Args> constexpr auto operator()(Args &&...args) & {
    return call(f, g, std::forward<Args>(args)...);
  }

  template <class... Args> constexpr auto operator()(Args &&...args) const & {
    return call(f, g, std::forward<Args>(args)...);
  }

  template <class... Args> constexpr auto operator()(Args &&...args) && {
    return call(std::move(f), std::move(g), std::forward<Args>(args)...);
  }

  template <class... Args> constexpr auto operator()(Args &&...args) const && {
    return call(std::move(f), std::move(g), std::forward<Args>(args)...);
  }
};

template <class F, class G> constexpr auto compose(F &&f, G &&g) {
  return compose_fn<std::remove_cvref_t<F>, std::remove_cvref_t<G>>(
      std::forward<F>(f), std::forward<G>(g));
}

template <typename F> struct pipeable {
private:
  F f;

public:
  constexpr explicit pipeable(F &&f_p) noexcept : f(std::forward<F>(f_p)) {}

  template <typename... Xs>
    requires std::invocable<F, Xs...>
  constexpr auto operator()(Xs &&...xs) const {
    return std::invoke(f, std::forward<Xs>(xs)...);
  }

  template <typename... Xs> constexpr auto operator()(Xs &&...xs) const {
    using FType = decltype(rd::bind_back(f, std::forward<Xs>(xs)...));
    return pipeable<FType>{rd::bind_back(f, std::forward<Xs>(xs)...)};
  }

  template <typename F1, typename F2>
  friend constexpr auto operator|(pipeable<F1> p1, pipeable<F2> p2);
};

template <typename Arg, typename F>
constexpr auto operator|(Arg &&arg, pipeable<F> const &p)
  requires std::invocable<F, Arg &&>
{
  return std::invoke(p, std::forward<Arg>(arg));
}

template <typename F1, typename F2>
constexpr auto operator|(pipeable<F1> p1, pipeable<F2> p2) {
  return pipeable{rd::compose(p2.f, p1.f)};
}

template <typename F> struct curried {
private:
  F f;

public:
  constexpr explicit curried(F &&f_p) noexcept : f(std::forward<F>(f_p)) {}

  template <typename... Xs>
    requires std::invocable<F, Xs...>
  constexpr auto operator()(Xs &&...xs) const {
    return std::invoke(f, std::forward<Xs>(xs)...);
  }

  template <typename... Xs> constexpr auto operator()(Xs &&...xs) const {
    using FType = decltype(std::bind_front(f, std::forward<Xs>(xs)...));
    return curried<FType>{std::bind_front(f, std::forward<Xs>(xs)...)};
  }
};

auto s_comb = rd::curried(
    [](auto &&f, auto ele) requires std::invocable<decltype(f), decltype(ele)> {
      return std::pair{ele, std::invoke(f, ele)};
    });
} // namespace rd

// }}}

// mutation to transformation {{{
auto make_sorted =
    rd::pipeable([]<typename Container, typename Comparator = std::less<>>(
        Container vec, Comparator &&cmp = std::less<>{}) {
      rng::sort(vec, std::forward<Comparator>(cmp));
      return vec;
    });

auto make_reversed = rd::pipeable([]<typename Container>(Container vec) {
  rng::reverse(vec);
  return vec;
});
// }}}

// codeforces template }}}

constexpr ll mod = 1e9 + 7;
using mii = ModInt::mod_int_t<mod>;

auto solve(ll _t) {
  auto const n = read<ll>();
  auto q = read<ll>();
  std::vector<ll> arr(n);
  for (ll i = 0; i < n; ++i) {
    auto const c = read<char>();
    arr[i] = c == '+' ? 1 : -1;
  }

  std::vector nums = arr;
  for (ll i = 0; i < n; ++i) {
    nums[i] *= (i % 2 ? -1 : 1);
  }

  std::vector prefix = nums;
  for (ll i = 1; i < n; ++i) {
    prefix[i] += prefix[i - 1];
  }

  auto get_sum = [&](ll i, ll j) {
    if (i == 0) {
      return prefix[j];
    }
    return prefix[j] - prefix[i - 1];
  };

  std::vector<ll> adj(n);
  adj[0] = prefix[0];
  for (ll i = 1; i < n; ++i)
    adj[i] = prefix[i] + prefix[i - 1];

  std::unordered_map<ll, std::set<ll>> mp;
  for (ll i = 0; i < n; ++i) {
    mp[adj[i]].insert(i);
  }

  auto to_del = [&](ll l, ll r) {
    auto const target = prefix[r] + (l == 0 ? 0 : prefix[l - 1]);
    return *mp[target].lower_bound(l);
  };

  while (q--) {
    auto const l = read<ll>() - 1;
    auto const r = read<ll>() - 1;
    auto const sum = get_sum(l, r);
    if (sum == 0) {
      std::cout << 0 << endl;
    } else if (sum % 2) {
      std::cout << 1 << endl;
      std::cout << to_del(l, r) + 1 << endl;
    } else {
      std::cout << 2 << endl;
      std::cout << to_del(l, r - 1) + 1 << ' ' << r + 1 << endl;
    }
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
