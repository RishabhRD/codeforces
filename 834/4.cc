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

auto num_factors(ll num, ll x) {
  ll ans = 0;
  while (num % x == 0) {
    num = num / x;
    ++ans;
  }
  return ans;
}

auto solveZ(ll n, ll max, ll z) {
  ll pow10 = std::pow(10ll, z);
  ll const m = (max / pow10) * pow10;
  ll const factors2 = num_factors(n, 2);
  ll const factors5 = num_factors(n, 5);
  ll const required2 = std::max(0ll, z - factors2);
  ll const required5 = std::max(0ll, z - factors5);
  ll const multiple = std::pow(2, required2) * std::pow(5, required5) * n;
  ll const lambda = m / multiple;
  return multiple * lambda;
}

auto const max_zero(ll n) {
  ll ans = 0;
  while (n > 9) {
    ++ans;
    n = n / 10;
  }
  return ans;
}

auto solve(ll n, ll m) {
  auto max = n * m;
  auto const maxPossible = max;
  for (int i = 1; i <= 18; ++i) {
    auto const ans = solveZ(n, maxPossible, i);
    if (ans != 0)
      max = ans;
  }
  return max;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<ll>();
    auto const m = read<ll>();
    std::cout << solve(n, m) << std::endl;
  }
}
