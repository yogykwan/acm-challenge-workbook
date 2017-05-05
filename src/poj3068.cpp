/*
 * POJ 3068: "Shortest" pair of paths
 * 题意：给出一个带权有向图，求两条从起点到终点中间无公共点的路的边权和最小值。
 * 类型：最小费
 * 算法：每个点拆为2个，起点和终点与其副本间连接容量2花费0的边，其余每个点和它的副本之间连接容量1花费0的边，输入的边连接开端和到达的副本容量1花费为边权。求解流为2的最小费用流即为答案。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;

struct Edge {
  Edge() {}

  Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}

  int v, cap, cost, rev;
};

vector<Edge> e[130];
int n;
int h[130], d[130];
int pv[130], pe[130];
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
  int m, tc = 0;
  while (scanf("%d%d", &n, &m) != EOF && n) {
    for (int i = 0; i < n << 1; ++i) e[i].clear();
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      AddEdge(u + n, v, 1, c);
    }
    AddEdge(0, n, 2, 0);
    AddEdge(n - 1, n - 1 + n, 2, 0);
    for (int i = 1; i < n - 1; ++i) {
      AddEdge(i, i + n, 1, 0);
    }
    n <<= 1;
    int ans = MinCostFlow(0, n - 1, 2);
    printf("Instance #%d: ", ++tc);
    if (ans == -1) printf("Not possible\n");
    else printf("%d\n", ans);
  }
  return 0;
}
