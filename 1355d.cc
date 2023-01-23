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

void dfs(ll i, ll s, ll n, std::vector<ll> &cur,
         std::vector<std::vector<ll>> &res) {
  if (i >= n) {
    if (s == 0)
      res.push_back(cur);
    else
      return;
  }
  if (s <= 0)
    return;
  for (int j = 1; j <= s; ++j) {
    cur.push_back(j);
    dfs(i + 1, s - j, n, cur, res);
    cur.pop_back();
  }
}

bool is_possible(std::vector<ll> const &nums, ll s) {
  std::vector prefix = nums;
  for (ll i = 1; i < nums.size(); ++i) {
    prefix[i] = nums[i] + prefix[i - 1];
  }
  auto sum = [&](ll i, ll j) {
    if (i == 0)
      return prefix[j];
    else
      return prefix[j] - prefix[i - 1];
  };
  for (ll k = 1; k <= s; ++k) {
    bool found = false;
    for (ll i = 0; i < prefix.size(); ++i) {
      for (ll j = i; j < prefix.size(); ++j) {
        if (sum(i, j) == k || sum(i, j) == s - k)
          found = true;
      }
    }
    if (!found)
      return true;
  }
  return false;
}

auto solve(ll n, ll s) {
  std::vector<ll> cur;
  std::vector<std::vector<ll>> res;
  dfs(0, s, n, cur, res);
  // for (auto &cur : res) {
  //   for (auto n : cur) {
  //     std::cout << n << ' ';
  //   }
  //   std::cout << std::endl;
  // }
  for (auto const &cur : res) {
    if (is_possible(cur, s)) {
      return true;
    }
  }
  return false;
}

int main() {
  auto const n = read<ll>();
  auto const s = read<ll>();
  if (s >= 2 * n) {
    std::cout << "YES" << std::endl;
    for (ll i = 0; i < n - 1; ++i) {
      std::cout << 1 << ' ';
    }
    std::cout << s - (n - 1) << std::endl;
    std::cout << n << std::endl;
  } else
    std::cout << "NO" << std::endl;
  // for (ll n = 1; n <= 10; ++n) {
  //   for (ll s = 1; s <= 10; ++s) {
  //     if (solve(n, s)) {
  //       std::cout << n << ' ' << s << std::endl;
  //     }
  //   }
  // }
}
