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

std::optional<std::vector<ll>> solve(std::vector<ll> input) {
  ll const n = input.size();
  std::sort(std::begin(input), std::end(input));
  ll low = 0;
  ll high = (n + 1) / 2;
  bool left_turn = true;
  std::vector<ll> nums(n);
  for (ll i = 0; i < n; ++i) {
    if (left_turn) {
      nums[i] = input[low++];
    } else {
      nums[i] = input[high++];
    }
    left_turn = !left_turn;
  }
  for (ll i = 0; i < n; ++i) {
    auto const left_idx = (i - 1 + n) % n;
    auto const right_idx = (i + 1) % n;
    bool const is_greater =
        nums[i] > nums[left_idx] && nums[i] > nums[right_idx];
    bool const is_smaller =
        nums[i] < nums[left_idx] && nums[i] < nums[right_idx];
    if (!(is_greater || is_smaller))
      return std::nullopt;
  }
  return nums;
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    auto const nums = solve(read_vec<ll>(n));
    if (nums.has_value()) {
      std::cout << "YES\n";
      for (auto n : nums.value()) {
        std::cout << n << ' ';
      }
      std::cout << '\n';
    } else {
      std::cout << "NO\n";
    }
  }
}
