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

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const k = read<ll>();
  auto const z = read<ll>();

  auto const nums = read_vec<ll>(n);

  std::vector<ll> prefix(n);
  prefix[0] = nums[0];
  for (ll i = 1; i < n; ++i) {
    prefix[i] = nums[i] + prefix[i - 1];
  }

  auto get_sum = [&](ll i, ll j) {
    if (i > j)
      return 0ll;
    if (i == 0)
      return prefix[j];
    return prefix[j] - prefix[i - 1];
  };

  ll max = 0;
  for (ll i = 0; i < n - 1; ++i) {
    ll rem_steps = k;
    rem_steps -= i;
    if (rem_steps < 0)
      continue;
    ll const prefix_sum = get_sum(0, i);
    ll const num_oscillation = std::min(rem_steps / 2, z);
    ll const osc_sum = num_oscillation * (nums[i] + nums[i + 1]);
    rem_steps -= 2 * num_oscillation;
    ll const suffix_sum = get_sum(i + 1, i + rem_steps);
    ll const total_sum = prefix_sum + osc_sum + suffix_sum;
    max = std::max(max, total_sum);
  }
  slog << endl;
  return max;
}
// solve: [a b c] a + b + c + b + c
// solve: [a b c d] a + b + a + b + c + d

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for;
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    std::cout << solve(i) << endl;
  }
}
