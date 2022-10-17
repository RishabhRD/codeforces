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

std::pair<ll, ll> solve() {
  auto const a = read<ll>();
  auto const b = read<ll>();
  auto const c = read<ll>();
  auto const d = read<ll>();
  auto const ab = a * b;
  std::vector<ll> fa;
  for (ll i = 1; i * i <= a; ++i) {
    if (a % i == 0) {
      fa.push_back(i);
      fa.push_back(a / i);
    }
  }
  std::vector<ll> fb;
  for (ll i = 1; i * i <= b; ++i) {
    if (b % i == 0) {
      fb.push_back(i);
      fb.push_back(b / i);
    }
  }
  for (ll const f1 : fa) {
    for (ll const f2 : fb) {
      // f1f2 | ab
      // ab = f1f2 * n
      ll const f1f2 = f1 * f2;
      ll const n = ab / f1f2;
      ll const x = (a / f1f2 + 1) * f1f2;
      ll const y = (b / n + 1) * n;
      if (x <= c and y <= d) {
        return {x, y};
      }
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
