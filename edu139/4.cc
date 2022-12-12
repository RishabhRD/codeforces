#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
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

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

using ll = long long;
constexpr ll mod = 1e9 + 7;

using safe_set = std::unordered_set<ll, custom_hash>;

template <typename T> using safe_map = std::unordered_map<ll, T>;

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

template <typename T> auto read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

template <typename Predicate>
std::pair<ll, ll> binary_search(ll lowa, ll lowb, ll higha, ll highb,
                                Predicate &&is_possible) {
  if (lowa >= higha)
    return {lowa, lowb};
  auto const mida = lowa + (higha - lowa) / 2;
  auto const midb = lowb + (highb - lowb) / 2;
  if (is_possible(mida, midb)) {
    return binary_search(mida + 1, midb + 1, higha, highb, is_possible);
  } else {
    return binary_search(lowa, lowb, mida, midb, is_possible);
  }
}

auto solve(ll a, ll b) {
  auto [x, y] = binary_search(a, b, a + 1e4, b + 1e4, [](auto a, auto b) {
    return std::gcd(a, b) == 1;
  });
  if (x == a + 1e4)
    std::cout << -1 << std::endl;
  std::cout << x - a - 1 << std::endl;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const a = read<ll>();
    auto const b = read<ll>();
    solve(a, b);
  }
}
