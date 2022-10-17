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

auto solve() {
  auto const n = read<int>() * 2;
  auto const cur = read<char>();
  auto str = read<std::string>();
  str += str;
  int last_g_pos = -1;
  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (str[i] == 'g')
      last_g_pos = i;
    else if (str[i] == cur and last_g_pos != -1) {
      ans = std::max(ans, last_g_pos - i);
    }
  }
  return ans;
}

int main() {
  auto t = read<int>();
  while (t--) {
    std::cout << solve() << std::endl;
  }
}
