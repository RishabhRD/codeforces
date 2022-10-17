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

using ll = long long;

ll get_min_y(ll ab, ll x) {
  auto const gcd = std::gcd(ab, x);
  auto const min_xy = ab * x / gcd;
  return min_xy / x;
}

std::pair<ll, ll> solve() {
  auto const a = read<ll>();
  auto const b = read<ll>();
  auto const c = read<ll>();
  auto const d = read<ll>();
  auto const ab = a * b;
  for (ll x = a + 1; x <= c; ++x) {
    auto const min_y = get_min_y(ab, x);
    for (ll i = 1; i * min_y <= d; ++i) {
      if (i * min_y > b)
        return {x, i * min_y};
    }
  }
  return {-1, -1};
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const [a, b] = solve();
    std::cout << a << ' ' << b << std::endl;
  }
}
