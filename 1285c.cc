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

auto make_prime_factors(ll n) {
  std::vector<ll> prime_factors;
  for (ll i = 2; i * i <= n; ++i) {
    ll cur = 1;
    while (n % i == 0) {
      n = n / i;
      cur *= i;
    }
    if (cur != 1)
      prime_factors.push_back(cur);
  }
  if (n != 1) {
    prime_factors.push_back(n);
  }
  return prime_factors;
}

auto solve(ll n) {
  auto const prime_factors = make_prime_factors(n);
  auto const sz = prime_factors.size();
  ll ans = INT64_MAX;
  for (ll i = 0; i < (1 << sz); ++i) {
    std::bitset<32> bs(i);
    ll first = 1;
    ll second = 1;
    for (ll i = 0; i < sz; ++i) {
      if (bs[i]) {
        first *= prime_factors[i];
      } else {
        second *= prime_factors[i];
      }
    }
    ans = std::min(ans, std::max(first, second));
  }
  return ans;
}

int main() {
  auto const n = read<ll>();
  auto const ans = solve(n);
  std::cout << n / ans << ' ' << ans << std::endl;
}
