#include <iostream>
#include <vector>

using namespace std;

const int mod = 998244353;

int count_valid_strings(int n, vector<vector<int>> &a) {
  vector<vector<int>> dp(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    dp[i][i] = (a[i][i] == 2 ? 2 : 1);
  }
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i <= n - len; i++) {
      int j = i + len - 1;
      if (a[i][j] == 1) {
        if (a[i][i] == a[j][j]) {
          dp[i][j] = dp[i + 1][j];
        } else {
          dp[i][j] = 0;
        }
      } else {
        dp[i][j] = (dp[i + 1][j] + dp[i][j - 1]) % mod;
      }
    }
  }
  return dp[0][n - 1];
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      cin >> a[i][j];
    }
  }
  cout << count_valid_strings(n, a) << endl;
  return 0;
}
