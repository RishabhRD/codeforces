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

bool is_even(int ele) { return ele % 2 == 0; }

auto solve() {
  auto const n = read<long long>();
  auto q = read<int>();
  auto const nums = read_vec<int>(n);
  auto sum = std::reduce(std::begin(nums), std::end(nums), 0ll);
  auto num_even = std::count_if(std::begin(nums), std::end(nums), is_even);
  auto num_odd =
      std::count_if(std::begin(nums), std::end(nums), std::not_fn(is_even));
  while (q--) {
    auto const parity = read<int>();
    auto const x = read<int>();
    if (parity == 0) {
      sum += num_even * x;
      if (!is_even(x)) {
        num_odd += num_even;
        num_even = 0;
      }
    } else {
      sum += num_odd * x;
      if (!is_even(x)) {
        num_even += num_odd;
        num_odd = 0;
      }
    }
    std::cout << sum << std::endl;
  }
}

int main() {
  auto t = read<int>();
  while (t--) {
    solve();
  }
}
