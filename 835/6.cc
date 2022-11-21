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

template <typename T> std::vector<T> read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

using ll = long long;

template <typename Predicate>
auto binary_search(ll low, ll high, Predicate &&isPossible) {
  auto const mid = low + ((high - low) / 2);
  if (low == high)
    return low;
  if (isPossible(mid)) {
    return binary_search(mid + 1, high, isPossible);
  } else {
    return binary_search(low, mid, isPossible);
  }
}

auto is_possible(ll k, ll c, ll d, std::vector<ll> const &nums) {
  auto const n = std::size(nums);
  ll sum = 0;
  for (ll i = 0; i < d; ++i) {
    auto const idx = (i % (k + 1));
    if (idx < n) {
      sum += nums[idx];
    }
  }
  return sum >= c;
}

auto solve(std::vector<ll> &nums, ll c, ll d) {
  std::sort(std::begin(nums), std::end(nums), std::greater<>());
  auto const ans = binary_search(
      0, INT64_MAX, [&](auto k) { return is_possible(k, c, d, nums); });
  if (ans <= 0) {
    std::cout << "Impossible" << std::endl;
  } else if (ans == INT64_MAX) {
    std::cout << "Infinity" << std::endl;
  } else {
    std::cout << ans - 1 << std::endl;
  }
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<ll>();
    auto const c = read<ll>();
    auto const d = read<ll>();
    auto nums = read_vec<ll>(n);
    solve(nums, c, d);
  }
}
