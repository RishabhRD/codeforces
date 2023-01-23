#include <bits/stdc++.h>

using namespace std;

std::tuple<int, int, int, int> rotate(int a, int b, int c, int d) {
  return {c, a, d, b};
}

auto solve(int a, int b, int c, int d) {
  for (int i = 0; i < 4; ++i) {
    auto [t1, t2, t3, t4] = rotate(a, b, c, d);
    if (t1 < t2 && t1 < t3 && t2 < t4 && t3 < t4)
      return true;
    else {
      a = t1;
      b = t2;
      c = t3;
      d = t4;
    }
  }
  return false;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (solve(a, b, c, d)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
