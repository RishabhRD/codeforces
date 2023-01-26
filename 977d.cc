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

enum class move { no, first, last };

move satisfy(ll n, std::vector<ll> const &nums) {
  if (nums.empty())
    return move::last;
  else if (n % 3 == 0 && n / 3 == nums.front())
    return move::first;
  else if (nums.back() * 2 == n)
    return move::last;
  else
    return move::no;
}

void dfs(ll i, std::vector<std::vector<ll>> const &graph, std::vector<ll> &res,
         std::vector<bool> &visited) {
  if (visited[i])
    return;
  visited[i] = true;
  for (auto n : graph[i]) {
    dfs(n, graph, res, visited);
  }
  res.push_back(i);
}

int main() {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  safe_map<ll> idx_mp;
  for (ll i = 0; i < n; ++i) {
    idx_mp[nums[i]] = i;
  }
  std::vector<std::vector<ll>> graph(n);
  for (ll i = 0; i < n; ++i) {
    auto const cur = nums[i];
    if (idx_mp.count(cur * 2)) {
      graph[i].push_back(idx_mp[cur * 2]);
    }
    if (cur % 3 == 0 && idx_mp.count(cur / 3)) {
      graph[i].push_back(idx_mp[cur / 3]);
    }
  }
  std::vector<ll> res;
  std::vector<bool> visited(n);
  for (ll i = 0; i < n; ++i) {
    dfs(i, graph, res, visited);
  }
  std::reverse(std::begin(res), std::end(res));
  for (auto n : res) {
    std::cout << nums[n] << ' ';
  }
  std::cout << std::endl;
}
