/*
 * POJ 2195: Going Home
 * 题意：给出一个矩阵，图中包含n个人和n个房子。为每个人指派一间房子，花费是两者的哈密顿距离。求最小总花费。
 * 类型：最小费
 * 算法：构造源s汇t，人和房子间建立容量1花费为距离的边，s与人、房子与t间建立容量1花费为0的边。Dijsktra得到最短路，然后在最短路上寻找增广路。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdlib>

using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;

char mat[110][110];
pii man[110], house[110];

struct Edge {
  Edge() {}

  Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}

  int v, cap, cost, rev;
};

vector<Edge> e[210];
int n;
int h[210], d[210];
int pv[210], pe[210];
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
  int r, c;
  while (scanf("%d%d", &r, &c) != EOF && r) {
    int nm = 0, nh = 0;
    for (int i = 0; i < r; ++i) {
      scanf("%s", mat[i]);
      for (int j = 0; j < c; ++j) {
        if (mat[i][j] == 'm') {
          man[nm++] = make_pair(i, j);
        } else if (mat[i][j] == 'H') {
          house[nh++] = make_pair(i, j);
        }
      }
    }
    n = nm * 2 + 2;
    int s = n - 2, t = n - 1;
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < nm; ++i) {
      AddEdge(s, i, 1, 0);
      AddEdge(i + nm, t, 1, 0);
    }
    for (int i = 0; i < nm; ++i) {
      for (int j = 0; j < nm; ++j) {
        AddEdge(i, nm + j, 1, abs(man[i].first - house[j].first) + abs(man[i].second - house[j].second));
      }
    }
    printf("%d\n", MinCostFlow(s, t, nm));
  }
  return 0;
}