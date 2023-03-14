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

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const nums = read_vec<ll>(n);
  auto const sum = std::reduce(std::begin(nums), std::end(nums), 0ll);
  if (sum % 3 != 0)
    return 0ll;
  std::vector<ll> prefixes;
  ll prefix_sum = 0;
  for (ll i = 0; i < n; ++i) {
    prefix_sum += nums[i];
    if (prefix_sum == sum / 3) {
      prefixes.push_back(i);
    }
  }

  std::vector<ll> suffixes;
  ll suffix_sum = 0;
  for (ll i = n - 1; i >= 0; --i) {
    suffix_sum += nums[i];
    if (suffix_sum == sum / 3) {
      suffixes.push_back(i);
    }
  }
  std::reverse(std::begin(suffixes), std::end(suffixes));

  ll ways = 0;
  for (auto n : prefixes) {
    auto const j = binary_search(0, suffixes.size(),
                                 [&](auto i) { return suffixes[i] <= n + 1; });
    ways += suffixes.size() - j;
  }

  return ways;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout << solve(0) << std::endl;
}
