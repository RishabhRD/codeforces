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

ll merge(ll low, ll mid, ll high, std::vector<ll> &nums) {
  ll j = mid + 1;
  ll cnt = 0;
  for (ll i = mid; i >= low; --i) {
    while (j <= high && nums[i] + nums[j] > 0) {
      ++j;
    }
    cnt += j - mid - 1;
  }
  std::sort(std::begin(nums) + low, std::begin(nums) + high + 1,
            std::greater<>{});
  return cnt;
}

ll num_pairs(ll low, ll high, std::vector<ll> &nums) {
  if (high <= low)
    return 0;
  auto const mid = (low + high) / 2;
  ll const left = num_pairs(low, mid, nums);
  ll const right = num_pairs(mid + 1, high, nums);
  ll const middle = merge(low, mid, high, nums);
  return left + middle + right;
}

auto solve(std::vector<ll> const &a, std::vector<ll> const &b) {
  ll const n = a.size();
  std::vector<ll> nums = a;
  for (ll i = 0; i < n; ++i) {
    nums[i] -= b[i];
  }
  return num_pairs(0, n - 1, nums);
}

int main() {
  auto const n = read<ll>();
  auto const a = read_vec<ll>(n);
  auto const b = read_vec<ll>(n);
  std::cout << solve(a, b) << std::endl;
}
