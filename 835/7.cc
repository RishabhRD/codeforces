#include <algorithm>
#include <array>
#include <bitset>
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

using ll = long long;

using graph_t = std::vector<std::unordered_map<ll, ll>>;

void dfs(ll i, ll cur, std::unordered_set<ll> &xors, std::vector<bool> &visited,
         graph_t const &graph) {
  visited[i] = true;
  for (auto const [n, w] : graph[i]) {
    if (!visited[n]) {
      auto res = cur ^ w;
      xors.insert(res);
      dfs(n, res, xors, visited, graph);
    }
  }
}

void dfs1(ll i, ll b, ll cur, std::unordered_set<ll> &xors,
          std::vector<bool> &visited, graph_t const &graph) {
  visited[i] = true;
  for (auto const [n, w] : graph[i]) {
    if (!visited[n] and n != b) {
      auto res = cur ^ w;
      xors.insert(res);
      dfs1(n, b, res, xors, visited, graph);
    }
  }
}

auto dfs1(graph_t const &graph, ll a, ll b) {
  auto const n = std::size(graph);
  std::unordered_set<ll> xors;
  std::vector visited(n, false);
  dfs1(a, b, 0, xors, visited, graph);
  return xors;
}

auto dfs(graph_t const &graph, ll a) {
  auto const n = std::size(graph);
  std::unordered_set<ll> xors;
  std::vector visited(n, false);
  dfs(a, 0, xors, visited, graph);
  return xors;
}

auto solve() {
  auto const n = read<ll>();
  auto a = read<ll>();
  auto b = read<ll>();
  --a;
  --b;
  std::vector<std::unordered_map<ll, ll>> graph(n);
  for (ll i = 0; i < n - 1; ++i) {
    auto u = read<ll>();
    auto v = read<ll>();
    auto w = read<ll>();
    --u;
    --v;
    graph[u][v] = w;
    graph[v][u] = w;
  }
  auto const xor1 = dfs1(graph, a, b);
  auto const xor2 = dfs(graph, b);
  for (auto ele : xor1) {
    if (xor2.count(ele))
      return true;
  }
  return false || xor2.count(0);
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
