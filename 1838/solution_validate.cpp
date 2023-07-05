#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ifstream qin{"bin/tmp"};
  std::ifstream sin{"bin/res"};

  std::vector<bool> is_prime(1e6 + 1, true);
  for (int i = 2; i <= 1e6; ++i) {
    if (is_prime[i]) {
      for (int j = i + i; j <= 1e6; j += i) {
        is_prime[j] = false;
      }
    }
  }
  is_prime[1] = false;
  is_prime[0] = false;

  int t;
  qin >> t;

  for (int _t = 1; _t <= t; ++_t) {
    int a, b;
    qin >> a >> b;

    std::vector<std::vector<int>> m(a, std::vector<int>(b));
    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < b; ++j) {
        sin >> m[i][j];
      }
    }

    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < b; ++j) {
        if (i != 0) {
          int const diff = std::abs(m[i][j] - m[i - 1][j]);
          if (is_prime[diff]) {
            std::cout << _t << std::endl;
            goto br;
          }
        }
      }
    }
  br:
    continue;
  }
}
