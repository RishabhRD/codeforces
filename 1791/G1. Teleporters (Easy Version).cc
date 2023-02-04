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

auto calc_res(std::vector<ll> res, ll rem_coins) {
  std::sort(std::begin(res), std::end(res));
  ll sum = 0;
  for (auto n : res) {
    if (n <= rem_coins) {
      rem_coins -= n;
      ++sum;
    } else {
      break;
    }
  }
  return sum;
}

ll solve(ll n, ll c, std::vector<ll> const &coins) {
  std::vector<ll> res;
  ll min = INT32_MAX;
  ll min_idx = -1;
  auto solve_for = [&](ll idx) {
    ll rem_coins = c - (coins[idx] + idx + 1);
    std::vector<ll> res;
    for (ll i = 0; i < n; ++i) {
      if (i == idx)
        continue;
      res.push_back(coins[i] + i + 1);
    }
    return calc_res(res, rem_coins);
  };
  for (ll i = 0; i < n; ++i) {
    ll cur_ans = coins[i] + i + 1;
    if (cur_ans < min) {
      min = cur_ans;
      min_idx = i;
    }
    min = std::min(cur_ans, min);
  }
  if (min <= c) {
    res.push_back(solve_for(min_idx));
  }
  if (res.size() == 0)
    return 0;
  return 1 + *std::min_element(std::begin(res), std::end(res));
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const c = read<ll>();
    auto const coins = read_vec<ll>(n);
    std::cout << solve(n, c, coins) << std::endl;
  }
}
