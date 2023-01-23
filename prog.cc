#include <bits/stdc++.h>

using namespace std;

using ll = long long;

std::vector<ll> solve(std::vector<ll> &A) {
  std::bitset<32> bs;
  ll cnt = 1;
  for (ll i = 0; i <= 31; ++i) {
    ll num_ones = 0;
    ll num_zeroes = 0;
    for (auto n : A) {
      if (std::bitset<32>(n)[i])
        ++num_ones;
      else
        ++num_zeroes;
    }
    if (num_ones == num_zeroes) {
      cnt *= 2;
      bs[i] = true;
    } else if (num_ones < num_zeroes) {
      bs[i] = false;
    } else {
      bs[i] = true;
    }
  }
  ll num = bs.to_ullong();
  ll sum = 0;
  for (auto n : A) {
    sum += num ^ n;
  }
  std::cout << sum << ' ' << cnt << std::endl;
  return std::vector<ll>({sum, cnt});
}

int main() {
  ll n;
  cin >> n;
  std::vector<ll> nums(n);
  for (auto &x : nums)
    cin >> x;
  solve(nums);
}
