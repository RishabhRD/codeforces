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

template <typename T> using matrix_t = std::vector<std::vector<T>>;
template <typename T> using cuboid_t = std::vector<std::vector<std::vector<T>>>;

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

// 0 0 -> 0
// 1 0 -> 1
// 0 1 -> 2
// 1 1 -> 3

bool dfs(ll i, ll a, ll b, std::vector<std::pair<ll, ll>> const &nums,
         cuboid_t<ll> &dp, cuboid_t<std::tuple<ll, ll, ll>> &decision) {
  // slog << i << ' ' << a << ' ' << b << ' ' << nums.size() << endl;
  if (i >= nums.size()) {
    return a == b;
  }

  if (dp[i][a][b] != -1)
    return dp[i][a][b];

  bool ans = false;
  if (nums[i].second == 2) {
    if (dfs(i + 1, a + 1, b + 1, nums, dp, decision)) {
      ans = true;
      decision[i][a][b] = {i + 1, a + 1, b + 1};
    } else if (dfs(i + 1, a, b, nums, dp, decision)) {
      ans = true;
      decision[i][a][b] = {i + 1, a, b};
    }
  } else {
    if (dfs(i + 1, a + 1, b, nums, dp, decision)) {
      ans = true;
      decision[i][a][b] = {i + 1, a + 1, b};
    } else if (dfs(i + 1, a, b + 1, nums, dp, decision)) {
      ans = true;
      decision[i][a][b] = {i + 1, a, b + 1};
    } else if (nums[i].second > 1) {
      if (dfs(i + 1, a, b, nums, dp, decision)) {
        ans = true;
        decision[i][a][b] = {i + 1, a, b};
      }
    }
  }

  return dp[i][a][b] = ans;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);

  std::vector<ll> freq(101, 0ll);
  for (auto n : nums) {
    ++freq[n];
  }

  std::vector<std::pair<ll, ll>> freq_nums;
  for (ll i = 1; i <= 100; ++i) {
    if (freq[i] > 0) {
      freq_nums.push_back({i, freq[i]});
    }
  }

  cuboid_t<std::tuple<ll, ll, ll>> decision(
      n, std::vector(n, std::vector<std::tuple<ll, ll, ll>>(n)));
  cuboid_t<ll> dp(n, std::vector(n, std::vector(n, -1ll)));

  std::vector<std::pair<ll, ll>> distribution(101);

  if (dfs(0, 0, 0, freq_nums, dp, decision)) {
    ll i = 0;
    ll a = 0;
    ll b = 0;
    for (; i < freq_nums.size();) {
      auto const [new_i, new_a, new_b] = decision[i][a][b];
      auto const cur = freq_nums[i].first;
      auto const freq = freq_nums[i].second;
      if (new_a > a && new_b > b) {
        distribution[cur] = {1, 1};
      } else if (new_a == a && new_b == b) {
        distribution[cur] = {0, freq};
      } else if (new_a > a) {
        distribution[cur] = {1, freq - 1};
      } else {
        distribution[cur] = {freq - 1, 1};
      }
      i = new_i;
      a = new_a;
      b = new_b;
    }
    std::cout << "YES" << endl;
    for (auto n : nums) {
      if (distribution[n].first > 0) {
        std::cout << "A";
        distribution[n].first--;
      } else {
        std::cout << "B";
      }
    }
  } else {
    std::cout << "NO" << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
