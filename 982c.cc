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

template <typename Container, typename Comparator = std::less<>>
auto make_sorted(Container vec, Comparator &&cmp = std::less<>{}) {
  std::sort(std::begin(vec), std::end(vec), cmp);
  return vec;
}

template <typename Container> auto make_reversed(Container vec) {
  std::reverse(std::begin(vec), std::end(vec));
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

ll subtree_size_of(ll i, ll parent, std::vector<std::vector<ll>> const &tree,
                   std::vector<ll> &subtree_size) {
  ll sum = 0;
  for (auto n : tree[i]) {
    if (n != parent) {
      sum += subtree_size_of(n, i, tree, subtree_size);
    }
  }
  return subtree_size[i] = sum + 1;
}

ll max_cut(ll i, ll parent, std::vector<std::vector<ll>> const &tree,
           std::vector<ll> const &subtree_size) {
  ll sum = 0;
  for (auto n : tree[i]) {
    if (n != parent) {
      if (subtree_size[n] % 2 == 0) {
        sum += 1 + max_cut(n, i, tree, subtree_size);
      } else {
        sum += max_cut(n, i, tree, subtree_size);
      }
    }
  }
  return sum;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  std::vector graph(n, std::vector<ll>());
  for (ll i = 0; i < n - 1; ++i) {
    auto const x = read<ll>() - 1;
    auto const y = read<ll>() - 1;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  if (n % 2)
    return -1ll;

  std::vector<ll> subtree_size(n);
  subtree_size_of(0, -1, graph, subtree_size);
  return max_cut(0, -1, graph, subtree_size);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << endl;
}
