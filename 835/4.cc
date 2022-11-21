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

auto solve(std::vector<int> nums) {
  nums.erase(std::unique(std::begin(nums), std::end(nums)), std::end(nums));
  auto const n = std::size(nums);
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    auto const left_condition = (i == 0) || (nums[i - 1] > nums[i]);
    auto const right_condition = (i == n - 1) || (nums[i] < nums[i + 1]);
    cnt += (left_condition && right_condition);
  }
  return cnt == 1;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    std::cout << (solve(read_vec<int>(n)) ? "YES" : "NO") << std::endl;
  }
}
