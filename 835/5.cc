#include <algorithm>
#include <array>
#include <bitset>
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

using ll = long long;

template <typename T> T read() {
  T t;
  std::cin >> t;
  return t;
}

template <typename T> std::vector<T> read_vec(ll n) {
  std::vector<T> vec(n);
  for (auto &ele : vec)
    std::cin >> ele;
  return vec;
}

template <typename T> std::vector<T> read_matrix(ll m, ll n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (ll i = 0; i < m; ++i) {
    for (ll j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

std::vector<ll> make_prefix(std::vector<ll> const &nums, ll e) {
  auto const n = std::size(nums);
  std::vector<ll> scan;
  ll cur = 0;
  for (ll i = 0; i < n; ++i) {
    if (nums[i] == e) {
      ++cur;
    }
    scan.push_back(cur);
  }
  return scan;
}

ll solve(std::vector<ll> const &nums) {
  auto const scan_0 = make_prefix(nums, 0);
  auto const scan_1 = make_prefix(nums, 1);
  auto const num0 = [&](auto i, auto j) -> ll {
    if (j < i)
      return 0;
    if (i == 0)
      return scan_0[j];
    return scan_0[j] - scan_0[i - 1];
  };
  auto const num1 = [&](auto i, auto j) -> ll {
    if (j < i)
      return 0;
    if (i == 0)
      return scan_1[j];
    return scan_1[j] - scan_1[i - 1];
  };

  ll const n = std::size(nums);
  ll num_inversions = 0;
  for (ll i = 0; i < n; ++i) {
    if (nums[i] == 1) {
      auto const x = num0(i + 1, n - 1);
      num_inversions += x;
    }
  }
  auto max_inversions = num_inversions;
  for (ll i = 0; i < n; ++i) {
    ll cur = 0;
    if (nums[i] == 0) {
      cur = num_inversions + num0(i + 1, n - 1) - num1(0, i - 1);
    } else {
      cur = num_inversions - num0(i + 1, n - 1) + num1(0, i - 1);
    }
    max_inversions = std::max(max_inversions, cur);
  }
  return max_inversions;
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const nums = read_vec<ll>(n);
    std::cout << solve(nums) << std::endl;
  }
}
