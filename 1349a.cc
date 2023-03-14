#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
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
constexpr char endl = '\n';
template <typename T> using limits = std::numeric_limits<T>;

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

ll lcm(ll a, ll b) { return (a * b) / std::gcd(a, b); }

ll power(ll n, ll x) {
  if (x == 0)
    return 1;
  auto ans = power(n, x / 2);
  ans = (ans * ans) % mod;
  if (x % 2)
    ans = (ans * n) % mod;
  return ans;
}

using pf = std::vector<std::vector<std::pair<ll, ll>>>;

auto solve(ll _t, pf const &prime_factors) {
  auto const n = read<ll>();
  auto const vec = read_vec<ll>(n);
  if (n == 1) {
    return vec[0];
  }
  std::unordered_map<ll, std::vector<ll>> factors;
  for (auto n : vec) {
    for (auto [k, v] : prime_factors[n]) {
      factors[k].push_back(v);
    }
  }
  for (auto &[k, v] : factors) {
    std::sort(std::begin(v), std::end(v));
  }

  ll ans = 1;
  for (auto &[k, v] : factors) {
    if (v.size() < n - 1) {
      continue;
    } else if (v.size() == n - 1) {
      ans *= power(k, v.front());
    } else {
      ans *= power(k, v[1]);
    }
  }
  return ans;
}

int main() {
  ll const max = 2 * 1e5;
  pf prime_factors(max + 1);
  for (ll i = 2; i <= max; ++i) {
    if (prime_factors[i].empty()) {
      for (ll j = i; j <= max; j += i) {
        ll k = j;
        ll sum = 0;
        while (k % i == 0) {
          k /= i;
          ++sum;
        }
        prime_factors[j].push_back({i, sum});
      }
    }
  }
  std::cout << solve(0, prime_factors) << std::endl;
}
