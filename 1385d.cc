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

template <typename F> ll num_steps(ll i, ll j, char c, F &&cnt_of) {
  if (i == j) {
    return 1 - cnt_of(c, i, j);
  }

  ll const len = (j - i + 1) / 2;
  auto const mid = (i + j) / 2;
  ll const left =
      len - cnt_of(c, mid + 1, j) + num_steps(i, mid, c + 1, cnt_of);
  ll const right =
      len - cnt_of(c, i, mid) + num_steps(mid + 1, j, c + 1, cnt_of);

  return std::min(left, right);
}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const str = read<std::string>();

  std::vector<std::vector<ll>> freq_pref;
  for (char c = 'a'; c <= 'z'; ++c) {
    std::vector<ll> cnt;
    ll cur_cnt = 0;
    for (auto cur : str) {
      if (cur == c) {
        ++cur_cnt;
      }
      cnt.push_back(cur_cnt);
    }
    freq_pref.push_back(std::move(cnt));
  }

  auto get_cnt = [&](char c, ll i, ll j) {
    if (i == 0) {
      return freq_pref[c - 'a'][j];
    }
    return freq_pref[c - 'a'][j] - freq_pref[c - 'a'][i - 1];
  };

  return num_steps(0, n - 1, 'a', get_cnt);
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
    std::cout << solve(i) << endl;
  }
}
