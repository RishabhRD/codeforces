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

auto solve(std::vector<int> const &nums, int sum) {
  std::unordered_set<int> st{std::begin(nums), std::end(nums)};
  for (int i = 1; sum > 0; ++i) {
    if (!st.count(i)) {
      sum -= i;
      st.insert(i);
    }
  }
  if (sum < 0)
    return false;
  for (int i = 1; !st.empty(); ++i) {
    if (!st.count(i)) {
      return false;
    } else {
      st.erase(i);
    }
  }
  return true;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    auto const sum = read<int>();
    auto const nums = read_vec<int>(n);
    if (solve(nums, sum)) {
      std::cout << "Yes" << std::endl;
    } else {
      std::cout << "No" << std::endl;
    }
  }
}
