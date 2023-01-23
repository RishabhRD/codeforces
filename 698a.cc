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

// 0 -> 0 0
// 1 -> 0 1
// 2 -> 1 0
// 3 -> 1 1

ll dfs(ll i, bool gym, bool contest, std::vector<ll> const &nums,
       std::vector<std::vector<std::vector<ll>>> &dp) {
  if (i >= std::size(nums))
    return 0;
  if (dp[i][gym][contest] != -1)
    return dp[i][gym][contest];
  ll ans = 0;
  if (nums[i] == 0) {
    ans = 1 + dfs(i + 1, false, false, nums, dp);
  } else if (nums[i] == 1) {
    if (contest) {
      ans = 1 + dfs(i + 1, false, false, nums, dp);
    } else {
      ans = std::min(1 + dfs(i + 1, false, false, nums, dp),
                     dfs(i + 1, false, true, nums, dp));
    }
  } else if (nums[i] == 2) {
    if (gym) {
      ans = 1 + dfs(i + 1, false, false, nums, dp);
    } else {
      ans = std::min(1 + dfs(i + 1, false, false, nums, dp),
                     dfs(i + 1, true, false, nums, dp));
    }
  } else {
    if (contest && gym) {
      ans = 1 + dfs(i + 1, false, false, nums, dp);
    } else if (contest) {
      ans = std::min(dfs(i + 1, true, false, nums, dp),
                     1 + dfs(i + 1, false, false, nums, dp));
    } else if (gym) {
      ans = std::min(dfs(i + 1, false, true, nums, dp),
                     1 + dfs(i + 1, false, false, nums, dp));
    } else {
      ans = std::min({
          1 + dfs(i + 1, false, false, nums, dp),
          dfs(i + 1, false, true, nums, dp),
          dfs(i + 1, true, false, nums, dp),
          dfs(i + 1, true, true, nums, dp),
      });
    }
  }
  return dp[i][gym][contest] = ans;
}

auto solve(std::vector<ll> const &nums) {
  auto const n = nums.size();
  std::vector dp(n, std::vector(2, std::vector(2, -1ll)));
  std::cout << dfs(0, false, false, nums, dp) << std::endl;
}

int main() {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  solve(nums);
}
