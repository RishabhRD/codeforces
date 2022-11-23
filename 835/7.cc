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

template <typename T> std::vector<T> read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

using graph_t = std::vector<std::vector<std::pair<ll, ll>>>;

void dfs(ll i, ll cur, safe_set &xors, ll prev, graph_t const &graph) {
  for (auto const [n, w] : graph[i]) {
    if (n != prev) {
      auto const new_xor = cur ^ w;
      xors.insert(new_xor);
      dfs(n, new_xor, xors, i, graph);
    }
  }
}

bool dfs1(ll i, ll b, ll cur, safe_set const &xors, ll prev,
          graph_t const &graph) {
  bool ans = false;
  for (auto const [n, w] : graph[i]) {
    if (n != prev && n != b) {
      auto const new_xor = cur ^ w;
      if (xors.count(new_xor))
        return true;
      ans = ans || dfs1(n, b, new_xor, xors, i, graph);
    }
  }
  return ans;
}

auto dfs1(graph_t const &graph, ll a, ll b, safe_set const &xors) {
  auto const n = std::size(graph);
  return dfs1(a, b, 0, xors, -1, graph);
}

auto dfs(graph_t const &graph, ll a) {
  auto const n = std::size(graph);
  safe_set xors;
  dfs(a, 0, xors, -1, graph);
  return xors;
}

bool solve() {
  auto const n = read<ll>();
  auto a = read<ll>();
  auto b = read<ll>();
  --a;
  --b;
  graph_t graph(n);
  for (ll i = 0; i < n - 1; ++i) {
    auto u = read<ll>();
    auto v = read<ll>();
    auto w = read<ll>();
    --u;
    --v;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }
  auto const xors = dfs(graph, b);
  if (dfs1(graph, a, b, xors)) {
    return true;
  }
  return xors.count(0);
}

int main() {
  auto t = read<int>();
  while (t--) {
    if (solve()) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}
