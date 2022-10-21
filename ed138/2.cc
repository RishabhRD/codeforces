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

auto make_freq_pref(std::vector<int> const &nums) {
  std::vector<int> freq(101);
  for (auto x : nums)
    ++freq[x];
  for (int i = 1; i <= 100; ++i) {
    freq[i] += freq[i - 1];
  }
  return freq;
}

bool is_possible(int i, std::vector<int> freq_pref) {
  for (; i >= 1; --i) {
    if (freq_pref[i] < 1)
      return false;
    for (int j = 1; j <= i; ++j)
      --freq_pref[j];
    int j = i;
    for (; freq_pref[j] == freq_pref[i] and j > 0; --j) {
    }
    for (int k = j + 1; k <= i; ++k)
      --freq_pref[k];
  }
  return true;
}

template <typename Func> int binary_search(int low, int high, Func &&possible) {
  if (low >= high)
    return low;
  auto const mid = (low + high + 1) / 2;
  if (possible(mid)) {
    return binary_search(mid, high, possible);
  } else {
    return binary_search(low, mid - 1, possible);
  }
}

auto solve() {
  auto const n = read<int>();
  auto const nums = read_vec<int>(n);
  auto const freq_pref = make_freq_pref(nums);
  return binary_search(0, 100,
                       [&](auto num) { return is_possible(num, freq_pref); });
}

int main() {
  auto t = read<int>();
  while (t--) {
    std::cout << solve() << std::endl;
  }
}
