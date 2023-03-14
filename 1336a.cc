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

bool log_enabled = true;

class log_t {};

template <typename T> auto operator<<(log_t const &self, T const &ele) {
  if (log_enabled) {
    std::cerr << ele;
  }
  return self;
};

constexpr log_t slog{};

ll dfs(ll i, ll prev, ll cur_depth, std::vector<std::vector<ll>> const &graph,
       std::vector<ll> &depth, std::vector<ll> &size) {
  depth[i] = cur_depth;
  ll cur_size = 1;
  for (auto n : graph[i]) {
    if (n != prev) {
      cur_size += dfs(n, i, cur_depth + 1, graph, depth, size);
    }
  }
  return size[i] = cur_size;
}

ll dfs2(ll i, ll prev, std::vector<std::vector<ll>> const &graph,
        std::vector<ll> const &depth, std::vector<ll> const &size,
        std::set<ll> const &st) {
  if (st.count(i)) {
    return depth[i] * size[i];
  }
  ll sum = 0;
  for (auto n : graph[i]) {
    if (n != prev) {
      sum += dfs2(n, i, graph, depth, size, st);
    }
  }
  return sum;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const k = read<ll>();
  std::vector<std::vector<ll>> graph(n + 1);
  for (ll i = 0; i < n - 1; ++i) {
    auto const x = read<ll>();
    auto const y = read<ll>();
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  std::vector<ll> size(n + 1);
  std::vector<ll> depth(n + 1);
  dfs(1, 0, 0, graph, depth, size);
  std::vector<ll> nodes(n);
  std::iota(std::begin(nodes), std::end(nodes), 1);

  std::sort(std::begin(nodes), std::end(nodes), [&](auto a, auto b) {
    return (size[a] * depth[a] + (size[b] - 1) * (depth[b] + 1)) >
           (size[b] * depth[b] + (size[a] - 1) * (depth[a] + 1));
  });

  std::set<ll> start{std::begin(nodes), std::begin(nodes) + k};

  return dfs2(1, 0, graph, depth, size, start);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << endl;
}
