/*
 * POJ 3422: Kaka's Matrix Travels
 * 题意：给出一个矩阵，每个点的价值非负。从左上走到右下，每路过一个点将其价值累加入答案，并将该点置0。求走k次能收获的最大总价值。
 * 类型：最小费
 * 算法：把每个点拆为2个，之间连接容量k花费负价值的边。构造源s汇t，s与原节点、原节点的副本连容量k花费0的边。最小费用流求得的相反数即为答案。
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

vector<Edge> e[5010];
int n;
int h[5010], d[5010];
int pv[5010], pe[5010];
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
  int r, k;
  scanf("%d%d", &r, &k);
  n = r * r;
  int s, t;
  s = n * 2;
  t = s + 1;
  for (int i = 0; i < n; ++i) {
    int c;
    scanf("%d", &c);
    AddEdge(i, i + n, 1, -c);
    AddEdge(s, i, k, 0);
    AddEdge(i + n, t, k, 0);
    if (i % r) {
      AddEdge(i - 1 + n, i, k, 0);
    }
    if (i < n - r) {
      AddEdge(i + n, i + r, k, 0);
    }
  }
  n = t + 1;
  printf("%d\n", -MinCostFlow(s, t, k));
  return 0;
}
