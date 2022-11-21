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

template <typename T> auto read_matrix(int m, int n) {
  std::vector<std::vector<T>> vec(m, std::vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> vec[i][j];
    }
  }
  return vec;
}

using ll = long long;

void dfs(int i, std::vector<int> &cur,
         std::vector<std::unordered_set<int>> &res,
         std::vector<std::vector<int>> const &graph) {
  cur.push_back(i);
  for (auto ele : cur)
    res[i].insert(ele);
  for (auto n : graph[i]) {
    dfs(n, cur, res, graph);
  }
  cur.pop_back();
}

auto solve(std::vector<std::vector<int>> const &matrix) {
  auto const n = std::size(matrix);
  std::vector graph(n, std::vector<int>());
  std::vector indegree(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j]) {
        graph[i].push_back(j);
        ++indegree[j];
      }
    }
  }
  std::vector res(n, std::unordered_set<int>());
  std::queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }
  while (not std::empty(q)) {
    auto const top = q.front();
    q.pop();
    res[top].insert(top);
    for (auto n : graph[top]) {
      --indegree[n];
      for (auto e : res[top]) {
        res[n].insert(e);
      }
      if (indegree[n] == 0) {
        q.push(n);
      }
    }
  }
  for (auto const &st : res) {
    std::cout << st.size() << ' ';
    for (auto const ele : st)
      std::cout << ele + 1 << ' ';
    std::cout << std::endl;
  }
}

int main() {
  auto t = read<int>();
  while (t--) {
    auto const n = read<int>();
    std::vector matrix(n, std::vector(n, 0));
    for (int i = 0; i < n; ++i) {
      auto const str = read<std::string>();
      for (int j = 0; j < n; ++j) {
        matrix[i][j] = str[j] - '0';
      }
    }
    solve(matrix);
  }
}
