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

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const k = read<ll>();
    std::vector<ll> seq({0});
    std::vector<ll> cold({0});
    std::vector<ll> hot({0});
    for (ll i = 0; i < n; ++i)
      seq.push_back(read<ll>());
    for (ll i = 0; i < k; ++i)
      cold.push_back(read<ll>());
    for (ll i = 0; i < k; ++i)
      hot.push_back(read<ll>());
    std::vector dp(2, std::vector(k + 1, 0ll));
    for (ll i = n; i > 0; --i) {
      std::vector cur(2, std::vector(k + 1, 0ll));
      for (ll which = 0; which < 2; ++which) {
        for (ll other_val = 0; other_val <= k; ++other_val) {
          ll cur_process = seq[i];
          auto const [zero_process, one_process] = [&] {
            ll zero_process = 0, one_process = 0;
            if (which == 0) {
              zero_process = seq[i - 1];
              one_process = other_val;
            } else {
              zero_process = other_val;
              one_process = seq[i - 1];
            }
            return std::pair{zero_process, one_process};
          }();
          auto const to_zero =
              (cur_process == zero_process ? hot[cur_process]
                                           : cold[cur_process]) +
              dp[0][one_process];
          auto const to_one = (cur_process == one_process ? hot[cur_process]
                                                          : cold[cur_process]) +
                              +dp[1][zero_process];
          cur[which][other_val] = std::min(to_zero, to_one);
        }
      }
      dp = std::move(cur);
    }
    std::cout << std::min(dp[0][0], dp[1][0]) << std::endl;
  }
}
