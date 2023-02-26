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

void block_path(ll i, ll prev, ll cur, std::vector<bool> const &has_cat,
                std::vector<std::vector<ll>> const &tree,
                std::vector<bool> &blocked, ll m) {
  ll new_cur = 0;
  if (has_cat[i]) {
    new_cur = cur + 1;
  }
  // std::cerr << i << ' ' << new_cur << std::endl;
  if (new_cur > m) {
    blocked[i] = true;
    return;
  }
  for (auto n : tree[i]) {
    if (n != prev) {
      block_path(n, i, new_cur, has_cat, tree, blocked, m);
    }
  }
}

ll num_leaf(ll i, ll prev, std::vector<bool> const &blocked,
            std::vector<std::vector<ll>> const &tree) {
  if (blocked[i])
    return 0;
  if (tree[i].size() == 1) {
    if (tree.size() == 2)
      return 1;
    else if (i != 1) {
      return 1;
    }
  }
  ll sum = 0;
  for (auto n : tree[i]) {
    if (n != prev) {
      sum += num_leaf(n, i, blocked, tree);
    }
  }
  return sum;
}

int main() {
  auto const n = read<ll>();
  auto const m = read<ll>();
  std::vector<std::vector<ll>> tree(n + 1);
  std::vector<bool> has_cat(n + 1);
  for (ll i = 1; i <= n; ++i) {
    auto const tmp = read<ll>();
    has_cat[i] = tmp;
  }
  for (ll i = 0; i < n - 1; ++i) {
    auto const x = read<ll>();
    auto const y = read<ll>();
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  std::vector<bool> blocked(n + 1, false);
  block_path(1, 0, 0, has_cat, tree, blocked, m);
  // for (auto n : blocked)
  //   std::cerr << n << ' ';
  // std::cerr << std::endl;
  std::cout << num_leaf(1, 0, blocked, tree) << std::endl;
}
