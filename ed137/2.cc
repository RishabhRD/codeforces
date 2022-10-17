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

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    std::vector<int> ans(n);
    std::iota(std::begin(ans), std::end(ans), 1);
    std::swap(ans[1], ans.back());
    for (auto ele : ans) {
      std::cout << ele << ' ';
    }
    std::cout << std::endl;
  }
}
