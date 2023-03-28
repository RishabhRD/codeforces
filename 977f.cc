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

class dsu {
private:
  using ll = long long;
  std::vector<ll> parent_;
  std::vector<ll> size_;

public:
  dsu(ll n) : parent_(n), size_(n, 1) {
    std::iota(std::begin(parent_), std::end(parent_), 0);
  }

  ll find(ll n) {
    if (parent_[n] == n)
      return n;
    return parent_[n] = find(parent_[n]);
  }

  void combine(ll x, ll y) {
    auto const px = find(x);
    auto const py = find(y);
    if (px == py)
      return;
    if (size_[px] >= size_[py]) {
      size_[px] += size_[py];
      parent_[py] = px;
    } else {
      size_[py] += size_[px];
      parent_[px] = py;
    }
  }

  auto size(ll n) { return size_[find(n)]; }
};

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

auto build_graph(ll n, std::vector<ll> const &nums) {
  std::unordered_map<ll, std::vector<ll>> idx;
  for (ll i = 0; i < n; ++i) {
    idx[nums[i]].push_back(i);
  }
  for (auto &[k, v] : idx) {
    std::reverse(std::begin(v), std::end(v));
  }
  return idx;
}

ll dfs(ll i, std::vector<ll> const &nums,
       std::unordered_map<ll, std::vector<ll>> &graph, std::vector<ll> &dp) {
  if (dp[i] != -1)
    return dp[i];
  auto const e = nums[i];
  auto const jidx = binary_search(0, graph[e - 1].size(),
                                  [&](auto j) { return graph[e - 1][j] >= i; });
  if (jidx == graph[e - 1].size()) {
    return dp[i] = 1;
  }
  auto const j = graph[e - 1][jidx];
  return dp[i] = 1 + dfs(j, nums, graph, dp);
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  auto graph = build_graph(n, nums);
  ll max = 0;
  ll maxi = -1;
  std::vector dp(n, -1ll);
  for (ll i = 0; i < n; ++i) {
    ll const ans = dfs(i, nums, graph, dp);
    if (max < ans) {
      max = ans;
      maxi = i;
    }
  }
  std::cout << max << endl;
  std::vector<ll> ans;
  for (ll i = 0; i < max; ++i) {
    auto const e = nums[maxi];
    ans.push_back(maxi + 1);
    auto const jidx = binary_search(0, graph[e - 1].size(), [&](auto j) {
      return graph[e - 1][j] >= maxi;
    });
    if (jidx != graph[e - 1].size())
      maxi = graph[e - 1][jidx];
  }
  std::reverse(std::begin(ans), std::end(ans));
  for (auto n : ans)
    std::cout << n << ' ';
  std::cout << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
