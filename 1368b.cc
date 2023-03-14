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

int main() {
  auto const n = read<ll>();
  auto count_with_char = [](ll i) {
    auto const rep = i / 10;
    auto const once = i % 10;
    ll total = 1;
    for (ll i = 1; i <= 10; ++i) {
      if (i <= once) {
        total *= (rep + 1);
      } else {
        total *= rep;
      }
    }
    return total;
  };

  auto is_less_than_n = [&](ll i) { return count_with_char(i) < n; };
  auto const idx = binary_search(10, 1000, is_less_than_n);

  std::string_view cf = "codeforces";
  std::string res;
  ll const rep = idx / 10;
  ll const once = idx % 10;
  for (ll i = 0; i < 10; ++i) {
    ll cnt = rep;
    if (i < once) {
      ++cnt;
    }
    for (ll j = 0; j < cnt; ++j) {
      res += cf[i];
    }
  }
  std::cout << res << std::endl;
}
