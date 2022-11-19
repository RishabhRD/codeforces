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

ll solve(std::vector<ll> const &power, ll ind, ll green, ll blue, ll h) {
  if (ind == std::size(power)) {
    return 0;
  }
  ll const ast = power[ind];
  if (ast < h) {
    h += ast / 2;
    return 1 + solve(power, ind + 1, green, blue, h);
  }
  ll const aGreen = green ? solve(power, ind, green - 1, blue, h * 2) : 0;
  ll const aBlue = blue ? solve(power, ind, green, blue - 1, h * 3) : 0;
  return std::max(aGreen, aBlue);
}

auto solve(std::vector<ll> &power, ll green, ll blue, ll h) {
  std::sort(std::begin(power), std::end(power));
  return solve(power, 0, green, blue, h);
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    auto const h = read<int>();
    auto power = read_vec<ll>(n);
    std::cout << solve(power, 2, 1, h) << std::endl;
  }
}
