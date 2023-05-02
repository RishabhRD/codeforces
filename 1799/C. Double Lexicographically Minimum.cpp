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

auto do_adjustment(std::string &str, ll low, ll high) {
  std::unordered_map<char, ll> freq;
  for (ll i = low; i <= high; ++i)
    ++freq[str[i]];
  if (freq.size() != 2)
    return;
  auto const mid = (low + high) / 2;
  std::swap(str[high], str[mid]);
}

auto solve(std::string str) {
  ll const n = str.size();
  std::sort(std::begin(str), std::end(str));
  std::string res = str;
  ll low = 0;
  ll high = n - 1;
  ll cur = 0;
  std::optional<std::pair<ll, ll>> imbalance_idx;
  while (low < high) {
    res[low] = str[cur + 1];
    res[high] = str[cur];
    ++low;
    --high;
    cur += 2;
    if (str[cur - 2] != str[cur - 1]) {
      imbalance_idx = {low - 1, high + 1};
      break;
    }
  }
  while (low <= high) {
    res[low++] = str[cur++];
  }
  if (imbalance_idx.has_value()) {
    do_adjustment(res, imbalance_idx.value().first,
                  imbalance_idx.value().second);
  }
  auto other = res;
  std::reverse(std::begin(other), std::end(other));
  return std::max(std::move(res), std::move(other));
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto str = read<std::string>();
    std::cout << solve(std::move(str)) << std::endl;
  }
}
