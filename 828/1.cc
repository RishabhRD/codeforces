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

bool solve(int n, std::vector<int> const &nums, std::string_view const str) {
  std::unordered_map<int, char> mp;
  for (int i = 0; i < n; ++i) {
    auto const itr = mp.find(nums[i]);
    if (itr == mp.end()) {
      mp[nums[i]] = str[i];
    } else {
      if (itr->second != str[i])
        return false;
    }
  }
  return true;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    auto const nums = read_vec<int>(n);
    auto const str = read<std::string>();
    if (solve(n, nums, str)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}
