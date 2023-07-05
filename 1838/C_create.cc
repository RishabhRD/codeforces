#include <iostream>
int main() {
  int sum = 0;
  for (int i = 4; i <= 20; ++i) {
    for (int j = 4; j <= 20; ++j) {
      std::cout << i << ' ' << j << std::endl;
      ++sum;
    }
  }
  std::cout << sum << std::endl;
}
