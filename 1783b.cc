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

auto solve(ll n) {
  ll const N = n * n;
  ll left = 1;
  ll right = N;
  std::vector matrix(n, std::vector(n, -1ll));
  std::vector visited(n, std::vector(n, false));
  visited[0][0] = true;
  std::queue<std::tuple<ll, ll, bool>> q;
  q.push({0, 0, true});
  while (not std::empty(q)) {
    auto const [x, y, is_left] = q.front();
    q.pop();
    if (is_left) {
      matrix[x][y] = left++;
    } else {
      matrix[x][y] = right--;
    }
    if (x + 1 < n && !visited[x + 1][y]) {
      q.push({x + 1, y, !is_left});
      visited[x + 1][y] = true;
    }
    if (y + 1 < n && !visited[x][y + 1]) {
      q.push({x, y + 1, !is_left});
      visited[x][y + 1] = true;
    }
  }
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < n; ++j) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

int main() {
  auto t = read<ll>();
  while (t--) {
    auto const n = read<ll>();
    solve(n);
  }
}
