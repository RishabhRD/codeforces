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

ll make01(ll i, bool is_zero, std::string_view str,
          std::vector<std::vector<ll>> &dp) {
  if (i == str.size())
    return 0;
  if (is_zero) {
    if (str[i] == '0') {
      return dp[i][true] = std::min(make01(i + 1, true, str, dp),
                                    1 + make01(i + 1, false, str, dp));
    } else {
      return dp[i][true] = std::min(make01(i + 1, false, str, dp),
                                    1 + make01(i + 1, true, str, dp));
    }
  } else {
    if (str[i] == '0') {
      return dp[i][false] = 1 + make01(i + 1, false, str, dp);
    } else {
      return dp[i][false] = make01(i + 1, false, str, dp);
    }
  }
}

ll make10(ll i, bool is_one, std::string_view str,
          std::vector<std::vector<ll>> &dp) {
  if (i == str.size())
    return 0;
  if (is_one) {
    if (str[i] == '1') {
      return dp[i][true] = std::min(make10(i + 1, true, str, dp),
                                    1 + make10(i + 1, false, str, dp));
    } else {
      return dp[i][true] = std::min(make10(i + 1, false, str, dp),
                                    1 + make10(i + 1, true, str, dp));
    }
  } else {
    if (str[i] == '1') {
      return dp[i][false] = 1 + make10(i + 1, false, str, dp);
    } else {
      return dp[i][false] = make10(i + 1, false, str, dp);
    }
  }
}

auto solve(std::string_view str) {
  auto const n = str.size();
  std::vector dp1(n, std::vector(2, -1ll));
  std::vector dp2(n, std::vector(2, -1ll));
  return std::min(make01(0, true, str, dp1), make10(0, true, str, dp2));
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const str = read<std::string>();
    std::cout << solve(str) << std::endl;
  }
}
