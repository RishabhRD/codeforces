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

auto mod(int a, int n) { return (a % n + n) % n; }

std::optional<int> idx(std::vector<int> const &nums) {
  auto const n = std::size(nums);
  for (int i = 0; i < n; ++i) {
    if (nums[mod(i - 1, n)] != nums[mod(i + 1, n)]) {
      return i;
    }
  }
  return std::nullopt;
}

auto solve(std::vector<int> &nums) {
  auto ans = 0;
  while (!(nums.size() == 1 || nums.size() == 2)) {
    auto const i = idx(nums);
    if (i.has_value()) {
      nums.erase(std::begin(nums) + i.value());
      ++ans;
    } else {
      nums.pop_back();
    }
  }
  return ans + nums.size();
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    auto nums = read_vec<int>(n);
    std::cout << solve(nums) << std::endl;
  }
}
