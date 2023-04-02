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

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  ll max_sum = 0;
  ll max_idx = -1;
  for (ll i = 0; i < n; ++i) {
    std::vector<ll> floors(n);
    ll cur_sum = nums[i];
    floors[i] = nums[i];
    for (ll j = i - 1; j >= 0; --j) {
      floors[j] = std::min(floors[j + 1], nums[j]);
      cur_sum += floors[j];
    }
    for (ll j = i + 1; j < n; ++j) {
      floors[j] = std::min(floors[j - 1], nums[j]);
      cur_sum += floors[j];
    }
    if (cur_sum > max_sum) {
      max_sum = cur_sum;
      max_idx = i;
    }
  }
  std::vector<ll> floors(n);
  floors[max_idx] = nums[max_idx];
  for (ll j = max_idx - 1; j >= 0; --j) {
    floors[j] = std::min(floors[j + 1], nums[j]);
  }
  for (ll j = max_idx + 1; j < n; ++j) {
    floors[j] = std::min(floors[j - 1], nums[j]);
  }
  for (auto n : floors)
    std::cout << n << ' ';
  std::cout << endl;
}

template <typename T, typename GroupFunc> class segment_tree {
  GroupFunc func;
  ll n;
  std::vector<T> arr;

public:
  segment_tree(std::vector<T> const &arr, GroupFunc func)
      : func(std::move(func)), n(std::size(arr)), arr(n * 4) {
    build(1, 0, n - 1, arr);
  }

  T query(ll tl, ll tr) { return query(1, 0, n - 1, tl, tr); }

  void update(ll i, T const &val) {
    update(i, [val](auto e) { return val; });
  }

  template <typename F> void update(ll i, F &&f) { update(1, 0, n - 1, i, f); }

private:
  void build(ll i, ll l, ll r, std::vector<T> const &vec) {
    if (l == r) {
      arr[i] = vec[l];
    } else {
      auto const m = l + ((r - l) / 2);
      build(2 * i, l, m, vec);
      build(2 * i + 1, m + 1, r, vec);
      arr[i] = func(arr[2 * i], arr[2 * i + 1]);
    }
  }

  T query(ll i, ll l, ll r, ll tl, ll tr) {
    if (l == tl && r == tr)
      return arr[i];
    auto const m = l + ((r - l) / 2);
    if (tl >= l and tr <= m) {
      return query(2 * i, l, m, tl, tr);
    } else if (tl >= (m + 1) and tr <= r) {
      return query(2 * i + 1, m + 1, r, tl, tr);
    } else {
      auto const left = query(2 * i, l, m, tl, m);
      auto const right = query(2 * i + 1, m + 1, r, m + 1, tr);
      return func(left, right);
    }
  }

  template <typename F> void update(ll i, ll l, ll r, ll idx, F &&f) {
    if (l == r) {
      arr[i] = f(arr[i]);
      return;
    }
    auto const m = l + ((r - l) / 2);
    if (idx <= m) {
      update(2 * i, l, m, idx, f);
    } else {
      update(2 * i + 1, m + 1, r, idx, f);
    }
    arr[i] = func(arr[2 * i], arr[2 * i + 1]);
  }
};

template <typename T, typename GroupFunc>
segment_tree(std::vector<T> const &, GroupFunc) -> segment_tree<T, GroupFunc>;

template <typename T, typename F>
ll dfs(ll low, ll high, segment_tree<T, F> &stree,
       std::map<std::pair<ll, ll>,
                std::tuple<ll, std::pair<ll, ll>, std::pair<ll, ll>>> &mp) {
  if (low > high)
    return 0;
  if (low == high) {
    auto [val, idx] = stree.query(low, high);
    return val;
  }

  auto const [min_val, min_idx] = stree.query(low, high);
  auto const first =
      (min_idx - low + 1) * min_val + dfs(min_idx + 1, high, stree, mp);
  auto const second =
      (high - min_idx + 1) * min_val + dfs(low, min_idx - 1, stree, mp);
  if (first > second) {
    mp[{low, high}] = {min_val, {low, min_idx}, {min_idx + 1, high}};
  } else {
    mp[{low, high}] = {min_val, {min_idx, high}, {low, min_idx - 1}};
  }
  return std::max(first, second);
}

// auto solve(ll _t) {
//   auto const n = read<ll>();
//   auto const nums = read_vec<ll>(n);
//   std::vector<std::pair<ll, ll>> idx_vec;
//   for (ll i = 0; i < n; ++i) {
//     idx_vec.push_back({nums[i], i});
//   }
//   segment_tree stree(idx_vec, [](auto a, auto b) { return std::min(a, b); });
//   std::map<std::pair<ll, ll>,
//            std::tuple<ll, std::pair<ll, ll>, std::pair<ll, ll>>>
//       mp;
//   dfs(0, n - 1, stree, mp);
//   std::pair<ll, ll> cur = {0, n - 1};
//   std::vector<ll> res = nums;
//   while (mp.count(cur)) {
//     auto const [val, same, differ] = mp[cur];
//     for (ll i = same.first; i <= same.second; ++i) {
//       res[i] = val;
//     }
//     cur = differ;
//   }
//   for (auto n : res) {
//     std::cout << n << ' ';
//   }
//   std::cout << endl;
// }

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
