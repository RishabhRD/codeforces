#include <bits/stdc++.h>

using ll = long long;

constexpr static ll mod = 1e9 + 7;

void find_max_dist_node(
    ll i, ll parent, std::vector<std::vector<std::pair<ll, ll>>> const &graph,
    ll cur_dist, ll &max_dist, ll &max_node) {
  if (cur_dist > max_dist) {
    max_dist = cur_dist;
    max_node = i;
  }

  for (auto tmp : graph[i]) {
    auto const n = tmp.first;
    auto const w = tmp.second;
    if (n != parent) {
      find_max_dist_node(n, i, graph, cur_dist + w, max_dist, max_node);
    }
  }
}

ll find_max_dist_node(
    ll root, std::vector<std::vector<std::pair<ll, ll>>> const &graph) {
  ll max_dist = 0;
  ll max_node = root;

  find_max_dist_node(root, root, graph, 0, max_dist, max_node);

  return max_node;
}

void find_target(ll i, ll parent, ll target,
                 std::vector<std::vector<std::pair<ll, ll>>> const &graph,
                 ll cur_dist, ll &res) {
  if (i == target) {
    res = cur_dist;
  }

  for (auto tmp : graph[i]) {
    auto const n = tmp.first;
    auto const w = tmp.second;
    if (n != parent) {
      find_target(n, i, target, graph, cur_dist + w, res);
    }
  }
}

ll find_dist_to(ll root, ll target,
                std::vector<std::vector<std::pair<ll, ll>>> const &graph) {
  ll res = 0;
  find_target(root, root, target, graph, 0, res);
  return res;
}

bool contains_node(ll root, ll parent, ll target,
                   std::vector<std::vector<std::pair<ll, ll>>> const &graph,
                   std::vector<bool> &dp) {
  if (root == target)
    return dp[root] = true;

  for (auto [n, _] : graph[root]) {
    if (n != parent) {
      dp[root] = dp[root] || contains_node(n, root, target, graph, dp);
    }
  }

  return dp[root];
}

void calc_max_dist(ll root, ll parent, ll dist1, ll dist2,
                   std::vector<bool> const &contains_extreme1,
                   std::vector<bool> const &contains_extreme2,
                   std::vector<ll> &dp,
                   std::vector<std::vector<std::pair<ll, ll>>> const &graph) {
  dp[root] = std::max(dist1, dist2);
  for (auto tmp : graph[root]) {
    auto const n = tmp.first;
    auto const w = tmp.second;
    if (n != parent) {
      ll const new_dist1 = contains_extreme1[n] ? (dist1 - w) : (dist1 + w);
      ll const new_dist2 = contains_extreme2[n] ? (dist2 - w) : (dist2 + w);
      calc_max_dist(n, root, new_dist1, new_dist2, contains_extreme1,
                    contains_extreme2, dp, graph);
    }
  }
}

auto solve(ll _t) {}

class Solution {
public:
  std::vector<ll> longDrive(int n, std::vector<std::vector<int>> edges, int q,
                            std::vector<int> query) {
    std::vector graph(n, std::vector<std::pair<ll, ll>>());

    for (auto const &edge : edges) {
      auto const x = edge[0];
      auto const y = edge[1];
      auto const w = edge[2];
      graph[x].push_back({y, w});
      graph[y].push_back({x, w});
    }

    ll const extreme1 = find_max_dist_node(0, graph);
    ll const extreme2 = find_max_dist_node(extreme1, graph);

    std::vector<bool> contains_extreme1(n);
    std::vector<bool> contains_extreme2(n);
    contains_node(0, 0, extreme1, graph, contains_extreme1);
    contains_node(0, 0, extreme2, graph, contains_extreme2);

    std::vector<ll> res(n);
    ll const dist1 = find_dist_to(0, extreme1, graph);
    ll const dist2 = find_dist_to(0, extreme2, graph);
    calc_max_dist(0, 0, dist1, dist2, contains_extreme1, contains_extreme2, res,
                  graph);

    std::vector<ll> ans;
    for (auto q : query) {
      ans.push_back(res[q - 1]);
    }

    return ans;
  }
};
