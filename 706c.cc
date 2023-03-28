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

std::string reversed(std::string str) {
  std::reverse(std::begin(str), std::end(str));
  return str;
}

ll score(ll i, ll is_rev, std::vector<std::string> const &strs,
         std::vector<ll> const &nums, std::vector<std::vector<ll>> &dp) {
  ll const n = strs.size();
  if (i == n - 1) {
    return 0;
  }
  if (dp[i][is_rev] != -2)
    return dp[i][is_rev];
  std::string cur_str = is_rev ? reversed(strs[i]) : strs[i];
  ll ans = -1;
  if (cur_str <= strs[i + 1]) {
    ll const new_ans = score(i + 1, false, strs, nums, dp);
    if (new_ans >= 0) {
      if (ans < 0)
        ans = new_ans;
      else
        ans = std::min(ans, new_ans);
    }
  }
  if (cur_str <= reversed(strs[i + 1])) {
    ll const new_ans = score(i + 1, true, strs, nums, dp);
    if (new_ans >= 0) {
      if (ans < 0) {
        ans = nums[i + 1] + new_ans;
      } else {
        ans = std::min(ans, nums[i + 1] + new_ans);
      }
    }
  }
  return dp[i][is_rev] = ans;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  auto const strs = read_vec<std::string>(n);
  std::vector dp(n, std::vector(2, -2ll));
  ll const first = score(0, false, strs, nums, dp);
  ll const second = score(0, true, strs, nums, dp);
  if (first < 0 && second < 0)
    return -1ll;
  else if (first < 0)
    return second + nums[0];
  else if (second < 0)
    return first;
  else
    return std::min(first, second + nums[0]);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << endl;
}
