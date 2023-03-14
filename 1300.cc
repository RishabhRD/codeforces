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

template <typename Predicate>
ll binary_search(ll low, ll high, Predicate &&predicate) {
  if (low >= high)
    return low;
  auto const mid = low + (high - low) / 2;
  if (predicate(mid)) {
    return binary_search(mid + 1, high, predicate);
  } else {
    return binary_search(low, mid, predicate);
  }
}
// O(n log n + log R * log n)
// O(n log n)
class Solution {
public:
  int findBestValue(std::vector<int> &nums, int target) {
    std::sort(std::begin(nums), std::end(nums));
    ll const n = nums.size();
    std::vector<ll> prefix({0});
    for (auto n : nums) {
      prefix.push_back(prefix.back() + n);
    }
    auto diff_at = [&](ll val) {
      auto const high =
          std::upper_bound(std::begin(nums), std::end(nums), val) -
          std::begin(nums);
      auto const total_sum = prefix[high] + (n - high) * val;
      return std::abs(target - total_sum);
    };
    auto const val = binary_search(
        0, 1e6 + 1, [&](auto i) { return diff_at(i) > diff_at(i + 1); });
    return val;
  }
};

//[1, 2, 3]
//[0, 1, 3, 6]

using ll = long long;

// class Solution {
// public:
//   // O(n + nlogn + R logn)
//   // O((n + R)log n)
//   int findBestValue(std::vector<int> &arr, int target) {
//     ll const n = arr.size();
//     std::sort(std::begin(arr), std::end(arr)); // O(n log n)
//     std::vector<ll> prefix({0});
//     for (auto n : arr) {
//       prefix.push_back(prefix.back() + n);
//     } // O(n)
//     ll min_diff = INT64_MAX;
//     ll min_diff_value = -10;
//     for (ll value = 0; value <= 1e5; ++value) { // O(R log n)
//       auto j = std::upper_bound(std::begin(arr), std::end(arr), value) -
//                std::begin(arr);
//       auto const k = n - j;
//       auto const s = prefix[j];
//       auto const cur_diff = std::abs(target - (s + k * value));
//       if (cur_diff < min_diff) {
//         min_diff = cur_diff;
//         min_diff_value = value;
//       }
//     }
//     return min_diff_value;
//   }
// };
