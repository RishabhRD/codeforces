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

bool dolog = false;

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
  // std::cerr << rem_coins << std::endl;
  // for(auto n : res) std::cerr << n << ' ';
  // std::cerr << std::endl;
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
  // std::cout << sum << std::endl;
  return sum;
}

template <typename Predicate>
ll binary_search(ll low, ll high, Predicate &&predicate) {
  if (low >= high)
    return low;
  auto const mid = low + (high - low) / 2;
  if (predicate(mid)) {
    return binary_search(mid + 1, high, predicate);
  } else {
    return binary_search(low, mid, predicate);
  }
}

ll solve(ll n, ll c, std::vector<ll> const &coins) {
  std::vector<std::pair<ll, ll>> costs;
  for (ll i = 0; i < n; ++i) {
    costs.push_back({coins[i] + std::min(i + 1, n - i), coins[i] + i + 1});
  }
  std::sort(std::begin(costs), std::end(costs));
  std::vector<ll> prefix(n);
  prefix[0] = costs[0].first;
  for (ll i = 1; i < n; ++i) {
    prefix[i] = prefix[i - 1] + costs[i].first;
  }
  ll res = 0;
  for (ll i = 0; i < n; ++i) {
    auto rem = c - costs[i].second;
    if (rem >= 0) {
      auto const ans = binary_search(0, n, [&](auto idx) {
        ll price = prefix[idx];
        if (i <= idx) {
          price -= costs[i].first;
        }
        return price <= rem;
      });
      if(i < ans){
        res = std::max(res, ans);
      }else{
        res = std::max(res, 1  + ans);
      }
    }
  }
    return res;
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const c = read<ll>();
    auto const coins = read_vec<ll>(n);
    if (t == 0) {
      dolog = true;
    } else {
      dolog = false;
    }
    std::cout << solve(n, c, coins) << std::endl;
  }
}
