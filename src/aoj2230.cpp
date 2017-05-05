/*
 * AOJ 2230: How to Create a Good Game
 * 题意：给出一个带权有向无环图，在保证起点到终点的最长路不变前提下，可增加一些边的权。求最大能增加的边权总和。
 * 类型：最小费
 * 算法：输入的边两端连接容量INF花费为负边权的边，Dijkstra求最长路。从终点到起点连接容量无穷、花费为最长路的边。构造源s汇t，s与入度大于出度的点连容量度差花费的本容量1花费0的边，出度大的向t连类似的边。求得的最小费为所有圈的正权和，再加上负权和（输入边权和的相反数）即为答案。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;

int in[110], out[110];

struct Edge {
  Edge() {}

  Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}

  int v, cap, cost, rev;
};

vector<Edge> e[110];
int n;
int h[110], d[110];
int pv[110], pe[110];
priority_queue<pii, vector<pii>, greater<pii> > pq;

void AddEdge(int u, int v, int cap, int cost) {
  e[u].push_back(Edge(v, cap, cost, e[v].size()));
  e[v].push_back(Edge(u, 0, -cost, e[u].size() - 1));
}

int MinCostFlow(int s, int t, int f) {
  int ans = 0;
  memset(h, 0, sizeof(h));
  while (f > 0) {
    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
      int u = pq.top().second;
      int pre = pq.top().first;
      pq.pop();
      if (d[u] < pre) continue;
      for (int i = 0; i < e[u].size(); ++i) {
        Edge &te = e[u][i];
        int v = te.v;
        if (te.cap > 0 && d[v] > d[u] + h[u] - h[v] + te.cost) {
          d[v] = d[u] + h[u] - h[v] + te.cost;
          pv[v] = u;
          pe[v] = i;
          pq.push(make_pair(d[v], v));
        }
      }
    }

    if (d[t] == INF) {
      return -1;
    }
    for (int i = 0; i < n; ++i) {
      h[i] += d[i];
    }

    int cur = f;
    for (int i = t; i != s; i = pv[i]) {
      cur = min(cur, e[pv[i]][pe[i]].cap);
    }
    ans += cur * h[t];
    f -= cur;
    for (int i = t; i != s; i = pv[i]) {
      Edge &te = e[pv[i]][pe[i]];
      te.cap -= cur;
      e[i][te.rev].cap += cur;
    }
  }
  return ans;
}

int main() {
  int m;
  scanf("%d%d", &n, &m);
  int s = n, t = n + 1;
  int sum = 0;
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    AddEdge(u, v, INF, -c);
    sum += c;
    ++in[v];
    ++out[u];
  }
  int degree = 0;
  for (int i = 0; i < n; ++i) {
    if (in[i] > out[i]) {
      degree += in[i] - out[i];
    }
  }

  memset(d, 0x3f, sizeof(d));
  d[0] = 0;
  pq.push(make_pair(0, 0));
  while (!pq.empty()) {
    int u = pq.top().second;
    int pre = pq.top().first;
    pq.pop();
    if (d[u] < pre) continue;
    for (int i = 0; i < e[u].size(); ++i) {
      Edge &te = e[u][i];
      int v = te.v;
      if (te.cap > 0 && d[v] > d[u] + te.cost) {
        d[v] = d[u] + te.cost;
        pq.push(make_pair(d[v], v));
      }
    }
  }

  AddEdge(n - 1, 0, INF, -d[n - 1]);
  for (int i = 0; i < n; ++i) {
    if (in[i] > out[i]) {
      AddEdge(s, i, in[i] - out[i], 0);
    } else {
      AddEdge(i, t, out[i] - in[i], 0);
    }
  }
  n += 2;
  int ans = MinCostFlow(s, t, degree) - sum;
  printf("%d\n", ans);
  return 0;
}
