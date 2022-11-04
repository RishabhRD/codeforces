#include <algorithm>
#include <array>
#include <bitset>
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

template <typename T> std::vector<T> read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

using ll = long long;

auto solve(int m, int n, std::vector<int> const &cards) {
  auto const k = std::size(cards);
  std::unordered_set<int> st;
  int target = k;
  int i = 0;
  while (target >= 1) {
    if (st.count(target)) {
      st.erase(target);
      --target;
    } else if ((i < k) and cards[i] == target) {
      ++i;
      --target;
    } else {
      st.insert(cards[i]);
      ++i;
      if (st.size() > (m - 1) * (n - 1)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const m = read<int>();
    auto const n = read<int>();
    auto const k = read<int>();
    auto const cards = read_vec<int>(k);
    if (solve(m, n, cards)) {
      std::cout << "Ya" << std::endl;
    } else {
      std::cout << "tidak" << std::endl;
    }
  }
}
