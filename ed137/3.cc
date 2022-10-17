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

int dfs(std::vector<int> const &nums, std::string_view str, int i, int prev,
        std::vector<int> &dp0, std::vector<int> &dp1) {
  if (i >= std::size(nums))
    return 0;
  if (prev == 0) {
    if (dp0[i] != -1)
      return dp0[i];
  }
  if (prev == 1) {
    if (dp1[i] != -1) {
      return dp1[i];
    }
  }
  if (prev == 0) {
    if (str[i] == '1') {
      return dp0[i] = std::max(nums[i - 1] + dfs(nums, str, i + 1, 0, dp0, dp1),
                               nums[i] + dfs(nums, str, i + 1, 1, dp0, dp1));
    } else {
      return dp0[i] = dfs(nums, str, i + 1, 0, dp0, dp1);
    }
  } else {
    return dp1[i] = nums[i] * (str[i] - '0') +
                    dfs(nums, str, i + 1, str[i] - '0', dp0, dp1);
  }
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    auto str = read<std::string>();
    auto const nums = read_vec<int>(n);
    std::vector dp0(n, -1);
    std::vector dp1(n, -1);
    std::cout << (str[0] - '0') * nums[0] +
                     dfs(nums, str, 1, str[0] - '0', dp0, dp1)
              << std::endl;
  }
}
