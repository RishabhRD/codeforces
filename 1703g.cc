using ll = long long;

#include <iostream>
#include <set>
#include <vector>

constexpr ll mod = 1e9 + 7;

constexpr char endl = '\n';
template <typename T> using limits = std::numeric_limits<T>;

template <typename T> using matrix_t = std::vector<std::vector<T>>;
template <typename T> using cuboid_t = std::vector<std::vector<std::vector<T>>>;

// IO {{{
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

auto operator<<(log_t const &self, std::ostream &(*f)(std::ostream &)) {
  if (log_enabled) {
    std::cerr << f;
  }
  return self;
};

constexpr log_t slog{};
// }}}

auto solve(ll _t) {
  auto const n = read<ll>();
  auto const k = read<ll>();
  auto const nums = read_vec<ll>(n);

  auto get_suffix = [&](ll start) {
    ll cur_sum = 0;
    ll cur = 2;
    for (ll j = 0; j < 30; ++j, cur *= 2) {
      ll i = start + j;
      if (i >= nums.size())
        break;
      cur_sum += nums[i] / cur;
    }
    return cur_sum;
  };

  ll max = get_suffix(0);
  ll cur_sum = 0;
  for (ll i = 0; i < n; ++i) {
    cur_sum -= k;
    cur_sum += nums[i];
    max = std::max(max, cur_sum + get_suffix(i + 1));
  }
  std::cout << max << endl;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  auto t = read<ll>();
  std::set<ll> enabled_for{3};
  for (ll i = 0; i < t; ++i) {
    if (enabled_for.count(i) || enabled_for.size() == 0) {
      log_enabled = true;
    } else {
      log_enabled = false;
    }
    solve(i);
  }
}
