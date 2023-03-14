#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
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

auto solve() {}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    std::vector<std::pair<ll, ll>> monsters;
    for (ll i = 0; i < n; ++i) {
      auto const a = read<ll>();
      auto const b = read<ll>();
      monsters.push_back({a, b});
    }
    std::vector<ll> diff(n);
    for (ll i = 0; i < n; ++i) {
      auto const j = ((i - 1) + n) % n;
      diff[i] = std::max(0ll, monsters[i].first - monsters[j].second);
    }
    std::vector<ll> prefix(n);
    prefix[0] = diff[0];
    for (ll i = 1; i < n; ++i) {
      prefix[i] = diff[i] + prefix[i - 1];
    }
    auto get_sum = [&](ll i, ll j) {
      if (i > j)
        return 0ll;
      if (i == 0)
        return prefix[j];
      return prefix[j] - prefix[i - 1];
    };
    ll min = INT64_MAX;
    for (ll i = 0; i < n; ++i) {
      min = std::min(min, monsters[i].first + get_sum(0, i - 1) +
                              get_sum(i + 1, n - 1));
    }
    std::cout << min << endl;
  }
}
