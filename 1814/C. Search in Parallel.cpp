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

auto calc_cost(std::vector<int> const &first, std::vector<int> const &second,
               std::vector<int> const &r, int s1, int s2) {
  ll sum = 0;
  for (ll i = 0; i < first.size(); ++i) {
    sum += (i + 1) * r[first[i]] * s1;
  }
  for (ll i = 0; i < second.size(); ++i) {
    sum += (i + 1) * r[second[i]] * s2;
  }
  slog << sum << endl;
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const s1 = read<ll>();
  auto const s2 = read<ll>();

  auto const r = read_vec<ll>(n);

  std::vector<ll> nums(n);
  std::iota(std::begin(nums), std::end(nums), 0);

  std::sort(std::begin(nums), std::end(nums),
            [&](auto a, auto b) { return r[a] > r[b]; });

  std::vector<ll> first;
  std::vector<ll> second;

  for (auto n : nums) {
    ll const first_cost = (first.size() + 1) * s1;
    ll const second_cost = (second.size() + 1) * s2;
    if (first_cost <= second_cost) {
      first.push_back(n + 1);
    } else {
      second.push_back(n + 1);
    }
  }

  std::cout << first.size() << ' ';
  for (auto n : first) {
    std::cout << n << ' ';
  }
  std::cout << endl;
  std::cout << second.size() << ' ';
  for (auto n : second) {
    std::cout << n << ' ';
  }
  std::cout << endl;
}

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
    solve(i);
  }
}
