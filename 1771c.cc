#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, M = 2 * N + 5;

bool vis[N], ans;

void Sieve() {
  memset(vis, true, sizeof(vis));

  vis[0] = vis[1] = false;
  for (int i = 4; i < N; i += 2)
    vis[i] = false;
  for (int i = 3; i < N / i; i += 2) {
    if (!vis[i])
      continue;
    for (int j = i * i; j < N; j += i + i)
      vis[j] = false;
  }
}

int in[N], vid;
vector<int> primes;

void Gen() {
  for (int i = 2; i < N; ++i)
    if (vis[i])
      primes.emplace_back(i);
}

set<int> st;

void check(int x) {
  if (in[x] == vid) {
    ans = true;
    return;
  }

  in[x] = vid;
}

void fact(int x) {

  if (x < N && vis[x] == true) {
    check(x);
    return;
  }

  int idx = 0, sz = primes.size();

  while (x > 1 && idx < sz && x / primes[idx] >= primes[idx]) {

    if (x % primes[idx] == 0) {
      check(primes[idx]);
      while (x % primes[idx] == 0)
        x /= primes[idx];
    }

    ++idx;
  }

  if (x > 1) {
    if (x < N)
      return check(x), void();

    if (st.find(x) != st.end()) {
      ans = true;
      return;
    }

    st.emplace(x);
  }
}

void pre() {
  ++vid;
  st.clear();
}

int main() {
  Sieve();
  Gen();

  int t;
  scanf("%d", &t);
  while (t--) {
    pre();

    int n;
    scanf("%d", &n);

    ans = false;

    while (n--) {
      int x;
      scanf("%d", &x);
      fact(x);
    }

    puts(ans ? "YES" : "NO");
  }
}
