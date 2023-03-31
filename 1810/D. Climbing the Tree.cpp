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

auto solve(ll _t) {
  std::optional<std::pair<ll, ll>> height_guess;
  auto q = read<ll>();
  while (q--) {
    auto const t = read<ll>();
    if (t == 1) {
      auto const a = read<ll>();
      auto const b = read<ll>();
      auto const d = read<ll>();

      ll hl = 0;
      ll hh = 0;
      if (d == 1) {
        hl = 1;
        hh = a;
      } else {
        hh = (a - b) * (d - 1) + a;
        hl = std::max((a - b) * (d - 2) + a + 1, (a - b) * (d - 1) + 1);
      }
      if (height_guess.has_value()) {
        auto &[oldhl, oldhh] = height_guess.value();
        if (hl > oldhh || hl < oldhl) {
          std::cout << 0 << ' ';
        } else {
          oldhl = std::max(oldhl, hl);
          oldhh = std::min(oldhh, hh);
          std::cout << 1 << ' ';
        }
      } else {
        height_guess = std::pair{hl, hh};
        std::cout << 1 << ' ';
      }
    } else {
      auto const a = read<ll>();
      auto const b = read<ll>();
      if (!height_guess.has_value()) {
        std::cout << -1 << ' ';
      } else {
        auto const [_hl, _hh] = height_guess.value();
        auto const hl = _hl;
        auto const hh = _hh;
        auto const d = binary_search(
            0, 1e12, [&](auto d) { return d * (a - b) + a < hl; });
        // slog << d << ' ' << hl << ' ' << hh << endl;
        if (d * (a - b) + a < hh) {
          std::cout << -1 << ' ';
        } else {
          std::cout << d + 1 << ' ';
        }
      }
    }
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for{3};
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    solve(i);
  }
}
