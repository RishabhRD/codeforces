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

bool is_possible(std::string_view str) {
  ll const n = str.size();
  std::unordered_set<ll> ends;
  for (ll i = 1; i < n; ++i) {
    if (str[i] == 'B' && str[i - 1] == 'A') {
      ends.insert(i);
    }
  }
  for (ll i = 1; i < n; ++i) {
    if (str[i] == 'A' && str[i - 1] == 'B') {
      if (ends.size() > 0) {
        ll c1 = ends.count(i - 1);
        ll c2 = ends.count(i + 1);
        if (ends.size() > c1 + c2)
          return true;
      }
    }
  }
  return false;
}

int main() {
  auto str = read<std::string>();
  bool const p1 = is_possible(str);
  std::reverse(std::begin(str), std::end(str));
  bool const p2 = is_possible(str);
  if (p1 || p2) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}
