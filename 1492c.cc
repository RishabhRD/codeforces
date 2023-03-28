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

auto solve(ll _t) {
  auto const m = read<ll>();
  auto const n = read<ll>();
  auto const s = read<std::string>();
  auto const t = read<std::string>();
  std::vector<std::set<ll, std::greater<>>> idx(26);
  for (ll i = m - 1; i >= 0; --i) {
    idx[s[i] - 'a'].insert(i);
  }

  std::vector<ll> pos;
  {
    ll i = 0;
    for (auto c : t) {
      for (; i < m; ++i) {
        if (s[i] == c) {
          pos.push_back(i);
          ++i;
          break;
        }
      }
    }
  }

  ll max_diff = 0;
  ll max = m;
  for (ll i = n - 1; i > 0; --i) {
    auto const j = *(idx[t[i] - 'a'].upper_bound(max));
    max_diff = std::max(max_diff, j - pos[i - 1]);
    max = j;
  }

  return max_diff;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::set<ll> enabled_for;
  for (ll i = 0; i < 1; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    std::cout << solve(i) << endl;
  }
}
