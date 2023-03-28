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

bool log_enabled = true;

class log_t {};

template <typename T> auto operator<<(log_t const &self, T const &ele) {
  if (log_enabled) {
    std::cerr << ele;
  }
  return self;
};

constexpr log_t slog{};

auto convert(ll t, ll a, ll b) {
  if (a <= b) {
    a = std::min(a + t, b);
  } else {
    a = std::max(a - t, b);
  }
  // slog << "output: " << a << endl;
  return a;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const init = read<ll>();
  std::vector<std::tuple<ll, ll, ll>> vec;
  for (ll i = 0; i < n; ++i) {
    auto const t = read<ll>();
    auto const a = read<ll>();
    auto const b = read<ll>();
    vec.push_back({t, a, b});
  }

  auto [pa, pb] = std::pair{init, init};
  ll prev_time = 0;
  for (auto const &[t, a, b] : vec) {
    auto const d = t - prev_time;
    auto const na = pa - d;
    auto const nb = pb + d;
    if (na <= b && nb >= a) {
      pa = std::max(na, a);
      pb = std::min(nb, b);
      prev_time = t;
    } else {
      return false;
    }
  }

  return true;
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
    if (solve(i)) {
      std::cout << "YES" << endl;
    } else {
      std::cout << "NO" << endl;
    }
  }
}
