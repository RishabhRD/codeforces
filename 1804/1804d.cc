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

bool log_enabled = false;

class log_t {};

template <typename T> auto operator<<(log_t const &self, T const &ele) {
  if (log_enabled) {
    std::cerr << ele;
  }
  return self;
};

constexpr log_t slog{};

ll min_for(std::string_view str) {
  ll const n = str.size();
  ll count = 0;
  for (ll i = 1; i < n; ++i) {
    if (str[i] == '1' && str[i - 1] == '1') {
      ++count;
      ++i;
    }
  }
  auto const max = n / 4;
  auto const possible = std::min(count, max);
  auto const total = std::count(std::begin(str), std::end(str), '1');
  return total - possible;
}

ll max_for(std::string_view str) {
  ll const n = str.size();
  ll count = 0;
  for (ll i = 1; i < n; ++i) {
    if (str[i] != '1' || str[i - 1] != '1') {
      ++count;
      ++i;
    }
  }
  auto const max = n / 4;
  auto const possible = std::min(count, max);
  auto const rem = max - possible;
  auto const total = std::count(std::begin(str), std::end(str), '1');
  return total - rem;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const m = read<ll>();
  auto const strs = read_vec<std::string>(n);
  ll min = 0;
  ll max = 0;
  for (std::string_view str : strs) {
    min += min_for(str);
    max += max_for(str);
  }
  std::cout << min << ' ' << max << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
