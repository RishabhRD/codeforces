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

auto solve() {}

int main() {
  auto const n = read<ll>();
  auto const m = read<ll>();
  auto const t = read<ll>();
  ll const max_num = 30;
  std::vector<std::vector<ll>> prime_factors(max_num + 1);
  for (ll i = 2; i <= max_num; ++i) {
    if (prime_factors[i].size() == 0) {
      for (ll j = i; j <= max_num; j += i) {
        ll cur = j;
        while (cur % i == 0) {
          prime_factors[j].push_back(i);
          cur /= i;
        }
      }
    }
  }
  std::vector<std::vector<ll>> factorial;
  factorial.push_back(std::vector<ll>(max_num));
  for (ll i = 1; i <= max_num; ++i) {
    auto cur = factorial[i - 1];
    for (auto n : prime_factors[i]) {
      ++cur[n];
    }
    factorial.push_back(std::move(cur));
  }

  auto multiply = [&](std::vector<ll> a, std::vector<ll> const &b) {
    for (ll i = 1; i <= max_num; ++i) {
      a[i] += b[i];
    }
    return a;
  };

  auto div = [&](std::vector<ll> a, std::vector<ll> const &b) {
    for (ll i = 1; i <= max_num; ++i) {
      a[i] -= b[i];
    }
    return a;
  };

  auto ncr = [&](auto const n, auto const r) {
    auto const &ff = factorial[n];
    auto const &fr = factorial[r];
    auto const &fnr = factorial[n - r];
    auto tmp = div(ff, fr);
    return div(std::move(tmp), fnr);
  };

  auto npr = [&](auto const n, auto const r) {
    auto const &ff = factorial[n];
    auto const &fr = factorial[n - r];
    return div(ff, fr);
  };

  auto val = [&](auto const &f) {
    ll mul = 1;
    for (ll i = 1; i <= max_num; ++i) {
      for (ll j = 1; j <= f[i]; ++j) {
        mul *= i;
      }
    }
    return mul;
  };

  ll sum = 0;
  for (ll i = 4; i <= n; ++i) {
    ll const j = t - i;
    if (j < 1)
      break;
    else if (j > m) {
      continue;
    }
    sum += val(multiply(ncr(n, i), ncr(m, j)));
  }
  std::cout << sum << std::endl;
}
