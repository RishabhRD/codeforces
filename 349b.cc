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

bool num_comparator(std::vector<ll> const &a, std::vector<ll> const &b) {
  ll suma = 0;
  ll sumb = 0;
  for (ll i = 0; i < 9; ++i) {
    suma += a[i];
    sumb += b[i];
  }
  if (suma == sumb) {
    for (ll i = 8; i >= 0; --i) {
      if (a[i] < b[i])
        return true;
      else if (a[i] > b[i])
        return false;
    }
    return true;
  } else {
    return suma < sumb;
  }
}

char from_num(ll i) {
  if (i == 0)
    return '0';
  if (i == 1)
    return '1';
  if (i == 2)
    return '2';
  if (i == 3)
    return '3';
  if (i == 4)
    return '4';
  if (i == 5)
    return '5';
  if (i == 6)
    return '6';
  if (i == 7)
    return '7';
  if (i == 8)
    return '8';
  return '9';
}

auto solve(ll _t) {
  auto const v = read<ll>();
  auto const nums = read_vec<ll>(9);
  auto const min_itr =
      std::prev(std::min_element(std::rbegin(nums), std::rend(nums)).base());
  auto const min = *min_itr;
  auto const min_idx = min_itr - std::begin(nums);
  auto const times = v / min;
  auto rem = v % min;
  std::string res(times, from_num(min_idx + 1));
  for (ll i = 0; i < times; ++i) {
    for (ll j = 8; j >= 0; --j) {
      if (j > min_idx && rem + nums[min_idx] >= nums[j]) {
        res[i] = from_num(j + 1);
        rem += nums[min_idx];
        rem -= nums[j];
        break;
      }
    }
  }
  if (res.empty()) {
    std::cout << -1 << endl;
  } else {
    std::cout << res << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
