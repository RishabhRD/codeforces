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

char const constexpr *word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::string num_to_col(ll n) {
  std::string res;
  while (n) {
    auto idx = n % 26;
    if (idx == 0) {
      idx = 25;
    } else {
      idx--;
    }
    res += word[idx];
    n /= 26;
    if (idx == 25)
      --n;
  }
  std::reverse(std::begin(res), std::end(res));
  return res;
}

ll col_to_num(std::string_view str) {
  ll const n = str.size();
  ll res = 0;
  ll cur = 1;
  for (ll i = n - 1; i >= 0; --i) {
    auto const idx = (str[i] - 'A') + 1;
    res = res + (idx * cur);
    cur *= 26;
  }
  return res;
}

bool is_digit(char c) { return c >= '0' && c <= '9'; }

bool is_first(std::string_view str) {
  ll const n = str.size();
  for (ll i = 0; i < n - 1; ++i) {
    if (is_digit(str[i]) && str[i + 1] == 'C') {
      return true;
    }
  }
  return false;
}

std::pair<ll, ll> parse_first(std::string_view str) {
  auto const c_idx = std::find(std::begin(str), std::end(str), 'C');
  std::string row_str{std::next(std::begin(str)), c_idx};
  std::string col_str{std::next(c_idx), std::end(str)};
  ll row = std::stoi(row_str);
  ll col = std::stoi(col_str);
  return std::pair{row, col};
}

std::pair<ll, std::string> parse_second(std::string_view str) {
  auto const dig_start_itr =
      std::partition_point(std::begin(str), std::end(str),
                           [](auto c) { return c >= 'A' && c <= 'Z'; });
  auto const col_str = std::string{std::begin(str), dig_start_itr};
  auto const row_str = std::string{dig_start_itr, std::end(str)};
  auto const row = std::stoi(row_str);
  return std::pair{row, col_str};
}

auto solve(std::string_view str) {
  if (is_first(str)) {
    auto [row, col] = parse_first(str);
    auto const col_str = num_to_col(col);
    std::cout << col_str << row << std::endl;
  } else {
    auto [row, col_str] = parse_second(str);
    auto const col = col_to_num(col_str);
    std::cout << 'R' << row << 'C' << col << std::endl;
  }
}

int main() {
  auto const n = read<ll>();
  auto const strs = read_vec<std::string>(n);
  for (auto s : strs)
    solve(s);
}
