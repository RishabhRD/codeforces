#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
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

std::pair<std::list<ll>, std::list<ll>> next(std::list<ll> k1,
                                             std::list<ll> k2) {
  if (k1.empty() || k2.empty()) {
    return {k1, k2};
  }
  auto const first = k1.front();
  auto const second = k2.front();
  k1.pop_front();
  k2.pop_front();
  if (first > second) {
    k1.push_back(second);
    k1.push_back(first);
  } else {
    k2.push_back(first);
    k2.push_back(second);
  }
  return {k1, k2};
}

int main() {
  auto const n = read<ll>();
  auto const k1 = read<ll>();
  auto const k1s = read_vec<ll>(k1);
  auto const k2 = read<ll>();
  auto const k2s = read_vec<ll>(k2);
  std::list<ll> k1_list;
  std::list<ll> k2_list;
  for (auto k : k1s)
    k1_list.push_back(k);
  for (auto k : k2s)
    k2_list.push_back(k);
  ll fast_step = 1;
  auto [k1_list_prime, k2_list_prime] = next(k1_list, k2_list);
  if (k1_list_prime.empty() || k2_list_prime.empty()) {
    std::cout << fast_step << ' ';
    if (k1_list_prime.empty())
      std::cout << 2 << std::endl;
    else
      std::cout << 1 << std::endl;
    return 0;
  }
  while (k1_list != k1_list_prime || k2_list != k2_list_prime) {
    auto const slow_next = next(k1_list, k2_list);
    auto fast_next = next(k1_list_prime, k2_list_prime);
    ++fast_step;
    if (fast_next.first.empty() || fast_next.second.empty()) {
      std::cout << fast_step << ' ';
      if (fast_next.first.empty())
        std::cout << 2 << std::endl;
      else
        std::cout << 1 << std::endl;
      return 0;
    }
    fast_next = next(fast_next.first, fast_next.second);
    ++fast_step;
    if (fast_next.first.empty() || fast_next.second.empty()) {
      std::cout << fast_step << ' ';
      if (fast_next.first.empty())
        std::cout << 2 << std::endl;
      else
        std::cout << 1 << std::endl;
      return 0;
    }
    k1_list = slow_next.first;
    k2_list = slow_next.second;
    k1_list_prime = fast_next.first;
    k2_list_prime = fast_next.second;
  }
  std::cout << -1 << std::endl;
}
