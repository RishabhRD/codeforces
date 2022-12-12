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

bool dfs(std::string_view f, std::string_view s, ll i, ll state) {
  if (state == 0 || state == 1) {
    if (f[i] == 'W')
      return false;
  }
  if (state == 2 || state == 3) {
    if (s[i] == 'W')
      return false;
  }
  if (i == std::size(f) - 1)
    return true;
  if (state == 0) {
    if (s[i + 1] == 'B') {
      return dfs(f, s, i + 1, 1);
    } else {
      return dfs(f, s, i + 1, 0);
    }
  } else if (state == 1) {
    return dfs(f, s, i, 2);
  } else if (state == 2) {
    if (f[i + 1] == 'B') {
      return dfs(f, s, i + 1, 3);
    } else {
      return dfs(f, s, i + 1, 2);
    }
  } else {
    return dfs(f, s, i, 0);
  }
}

auto solve(std::string_view f, std::string_view s) {
  if (f[0] == 'B' and s[0] == 'B')
    return dfs(f, s, 0, 1) || dfs(f, s, 0, 3);
  else if (f[0] == 'B')
    return dfs(f, s, 0, 0);
  else if (s[0] == 'B') {
    return dfs(f, s, 0, 2);
  } else {
    return false;
  }
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<ll>();
    auto const f = read<std::string>();
    auto const s = read<std::string>();
    if (solve(f, s)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}
