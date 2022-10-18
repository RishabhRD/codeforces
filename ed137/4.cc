#include <algorithm>
#include <iostream>

template <typename T> T read() {
  T t;
  std::cin >> t;
  return t;
}

// precondition: a.len() <= b.len()
std::string string_or(std::string_view a, std::string b) {
  std::transform(std::crbegin(a), std::crend(a), std::crbegin(b),
                 std::rbegin(b), [](auto a, auto b) { return a | b; });
  return b;
}

auto trim(std::string str) {
  auto const first_zero = std::find(std::begin(str), std::end(str), '1');
  str.erase(std::begin(str), first_zero);
  return str;
}

std::string solve() {
  auto const _ = read<int>();
  auto const str = trim(read<std::string>());
  if (str.size() == 0)
    return "0";
  auto const first_zero_idx = std::distance(
      std::begin(str), std::find(std::begin(str), std::end(str), '0'));
  std::string_view s = str;
  auto const n = std::size(str);
  auto max = str;
  for (int i = 1; i <= first_zero_idx; ++i) {
    max = std::max(max, string_or(s.substr(0, n - i), str));
  }
  return max;
}

int main() { std::cout << solve() << std::endl; }
