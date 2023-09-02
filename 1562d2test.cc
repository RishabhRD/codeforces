#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <deque>
#include <exception>
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

using ll = long long;

int main() {
  std::string s = "+++-+-+---+-+-+---+-+-+-+-";
  std::vector<ll> nums;
  for (ll i = 0; i < 26; ++i) {
    if (s[i] == '+')
      nums.push_back(1);
    else
      nums.push_back(-1);
  }
  // for (ll i = 1; i <= 25; ++i) {
  //   std::cout << nums[i] << ' ';
  // }
  // std::cout << std::endl;

  for (ll i = 0; i < 26; ++i) {
    for (ll j = i; j < 26; ++j) {
      ll n;
      std::cin >> n;
      std::unordered_set<ll> skip;
      for (ll i = 0; i < n; ++i) {
        ll x;
        std::cin >> x;
        --x;
        skip.insert(x);
      }
      ll cur = 1;
      ll sum = 0;
      for (ll k = i; k <= j; ++k) {
        if (skip.count(k))
          continue;
        sum += nums[k] * cur;
        cur *= -1;
      }
      if (sum != 0) {
        std::cout << "Error: " << i << ' ' << j << std::endl;
        std::cerr << skip.size() << std::endl;
        for (auto n : skip)
          std::cout << n + 1 << std::endl;
        std::terminate();
      }
    }
  }
}
