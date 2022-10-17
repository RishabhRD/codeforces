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

class num_2_t {
  std::unordered_map<int, int> mp;

public:
  int operator()(int n) {
    if (mp.find(n) != mp.end())
      return mp[n];
    if (n % 2 == 1) {
      mp[n] = 0;
    } else {
      mp[n] = 1 + (*this)(n / 2);
    }
    return mp[n];
  }
};

int main() {
  num_2_t num_2;
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    auto const nums = read_vec<int>(n);
    int max_nums = 0;
    std::vector<int> idx_factors;
    for (int i = 1; i <= n; ++i) {
      idx_factors.push_back(num_2(i));
    }
    std::sort(std::begin(idx_factors), std::end(idx_factors),
              std::greater<int>{});
    auto total_2 = 0;
    for (auto const num : nums) {
      total_2 += num_2(num);
    }
    int i = 0;
    for (; i < std::size(idx_factors) and total_2 < n; ++i) {
      total_2 += idx_factors[i];
    }
    if (total_2 < n)
      std::cout << -1 << std::endl;
    else
      std::cout << i << std::endl;
  }
}
