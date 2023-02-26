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

ll get_max_sum(ll i, std::vector<ll> const &nums, std::vector<ll> &dp) {
  if (i >= nums.size())
    return 0;
  if (dp[i] != -1)
    return dp[i];
  return dp[i] = std::max(get_max_sum(i + 1, nums, dp),
                          nums[i] + get_max_sum(i + 2, nums, dp));
}

auto solve(std::vector<ll> &nums) {
  std::unordered_map<ll, ll> freq;
  for (auto n : nums)
    ++freq[n];
  std::vector<std::pair<ll, ll>> vec{std::begin(freq), std::end(freq)};
  std::sort(std::begin(vec), std::end(vec));
  std::vector<std::vector<ll>> scores(
      {std::vector<ll>({vec.front().first * vec.front().second})});
  for (ll i = 1; i < vec.size(); ++i) {
    if (vec[i].first != vec[i - 1].first + 1) {
      scores.push_back(std::vector<ll>({vec[i].first * vec[i].second}));
    } else {
      scores.back().push_back(vec[i].first * vec[i].second);
    }
  }
  ll sum = 0;
  for (auto const &score : scores) {
    std::vector<ll> dp(score.size(), -1ll);
    sum += get_max_sum(0, score, dp);
  }
  return sum;
}

int main() {
  auto const n = read<ll>();
  auto nums = read_vec<ll>(n);
  std::cout << solve(nums) << std::endl;
}
