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

using graph_t = std::vector<std::unordered_set<ll>>;

auto solve(graph_t const &graph, std::vector<ll> const &nums) {
  auto const n = graph.size();
  if (nums[0] != 0)
    return false;
  std::queue<ll> q;
  std::vector<bool> visited(n);
  visited[0] = true;
  q.push(0);
  ll idx = 0;
  while (not std::empty(q)) {
    auto const top = q.front();
    q.pop();
    auto const sz = graph[top].size() - 1;
    for (ll i = 0; i < sz; ++i) {
      ++idx;
      if (!graph[top].count(nums[idx])) {
        return false;
      }
      q.push(nums[idx]);
    }
  }
  return true;
}

int main() {
  auto const n = read<ll>();
  graph_t tree(n);
  for (ll i = 0; i < n - 1; ++i) {
    auto const a = read<ll>() - 1;
    auto const b = read<ll>() - 1;
    tree[a].insert(b);
    tree[b].insert(a);
  }
  tree[0].insert(0);
  std::vector<ll> nums;
  for (ll i = 0; i < n; ++i) {
    nums.push_back(read<ll>() - 1);
  }
  if (solve(tree, nums)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}
