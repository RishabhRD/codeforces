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

auto solve(std::vector<ll> const &nums) -> std::optional<std::pair<ll, ll>> {
  ll const n = nums.size();
  segment_tree min_stree{nums, [](auto a, auto b) { return std::min(a, b); }};
  segment_tree max_stree{nums, [](auto a, auto b) { return std::max(a, b); }};
  ll low = 0;
  ll high = n - 1;
  auto is_valid = [&](ll i, ll low, ll high) {
    auto const min_ele = min_stree.query(low, high);
    auto const max_ele = max_stree.query(low, high);
    return min_ele != nums[i] && max_ele != nums[i];
  };
  while (low <= high) {
    if (!is_valid(low, low, high)) {
      ++low;
    } else if (!is_valid(high, low, high)) {
      --high;
    } else {
      break;
    }
  }
  if (low > high) {
    return std::nullopt;
  }
  return std::pair{low, high};
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const nums = read_vec<ll>(n);
    auto const res = solve(nums);
    if (res.has_value()) {
      std::cout << res.value().first + 1 << ' ' << res.value().second + 1
                << std::endl;
    } else {
      std::cout << -1 << std::endl;
    }
  }
}
