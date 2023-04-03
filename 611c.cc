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

auto make_horizontal_structure(ll h, ll w,
                               std::vector<std::string> const &matrix) {
  matrix_t<ll> res(h, std::vector(w, 0ll));

  for (ll i = 0; i < h; ++i) {
    for (ll j = 1; j < w; ++j) {
      if (matrix[i][j - 1] == '.' && matrix[i][j] == '.')
        res[i][j] = 1;
    }
  }
  // for (ll i = 0; i < h; ++i) {
  //   for (ll j = 0; j < w; ++j) {
  //     slog << res[i][j] << ' ';
  //   }
  //   slog << endl;
  // }
  //
  // slog << endl;

  for (ll i = 0; i < h; ++i) {
    for (ll j = 1; j < w; ++j) {
      res[i][j] += res[i][j - 1];
    }
  }
  // for (ll i = 0; i < h; ++i) {
  //   for (ll j = 0; j < w; ++j) {
  //     slog << res[i][j] << ' ';
  //   }
  //   slog << endl;
  // }
  //
  // slog << endl;

  for (ll j = 0; j < w; ++j) {
    for (ll i = 1; i < h; ++i) {
      res[i][j] += res[i - 1][j];
    }
  }

  // for (ll i = 0; i < h; ++i) {
  //   for (ll j = 0; j < w; ++j) {
  //     slog << res[i][j] << ' ';
  //   }
  //   slog << endl;
  // }
  //
  // slog << endl;

  return res;
}

auto make_vertical_structure(ll h, ll w,
                             std::vector<std::string> const &matrix) {
  matrix_t<ll> res(h, std::vector(w, 0ll));

  for (ll j = 0; j < w; ++j) {
    for (ll i = 1; i < h; ++i) {
      if (matrix[i - 1][j] == '.' && matrix[i][j] == '.') {
        res[i][j] = 1;
      }
    }
  }

  for (ll j = 0; j < w; ++j) {
    for (ll i = 1; i < h; ++i) {
      res[i][j] += res[i - 1][j];
    }
  }

  for (ll i = 0; i < h; ++i) {
    for (ll j = 1; j < w; ++j) {
      res[i][j] += res[i][j - 1];
    }
  }

  return res;
}

auto solve(ll _t) {
  auto const h = read<ll>();
  auto const w = read<ll>();
  std::vector<std::string> input;
  for (ll i = 0; i < h; ++i) {
    input.push_back(read<std::string>());
  }

  auto const ho = make_horizontal_structure(h, w, input);
  auto const ve = make_vertical_structure(h, w, input);

  auto q = read<ll>();
  while (q--) {
    auto const l0 = read<ll>() - 1;
    auto const r0 = read<ll>() - 1;
    auto const l1 = read<ll>() - 1;
    auto const r1 = read<ll>() - 1;

    auto const horizontal_contribution =
        ho[l1][r1] - (l0 - 1 >= 0 ? ho[l0 - 1][r1] : 0) - ho[l1][r0] +
        (l0 - 1 >= 0 ? ho[l0 - 1][r0] : 0);
    auto const vertical_contribution = ve[l1][r1] - ve[l0][r1] -
                                       (r0 - 1 >= 0 ? ve[l1][r0 - 1] : 0) +
                                       (r0 - 1 >= 0 ? ve[l0][r0 - 1] : 0);

    std::cout << horizontal_contribution + vertical_contribution << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  solve(0);
}
