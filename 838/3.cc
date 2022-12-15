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
constexpr ll mod = 998244353;

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

ll mypower2(ll y) {
  ll x = 2;
  int res = 1;
  while (y > 0) {
    if (y & 1)
      res = (res * x) % mod;
    y = y >> 1; // y = y/2
    x = (x * x) % mod;
  }
  return res;
}

auto solve(std::string_view str) {
  ll num_zero = 0;
  ll num_one = 0;
  ll const n = std::size(str);
  ll ans = 1;
  if (str[0] == '0')
    num_zero = 1;
  else
    num_one = 1;
  for (ll i = 1; i < n; ++i) {
    ll total = 2 * i + 1;
    ll p = total;
    ll req = i + 1;
    if (str[i] == '0') {
      ++num_zero;
      num_zero = std::max(num_zero, req);
    } else {
      ++num_one;
      num_one = std::max(num_one, req);
    }
    p -= (num_zero + num_one);
    ans = (ans + mypower2(p)) % mod;
  }
  std::cout << ans << std::endl;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<ll>();
    auto const str = read<std::string>();
    solve(str);
  }
}
