/*
 * AOJ 2266: Cache Strategy
 * 题意：有n个重量不同的球和m个框，再给出一个可重复的放球序列。依照序列顺序将此刻不在框内的球放入，若选择放入的框已有球，则需花费新球数量的重量来替换。求最小总花费。
 * 类型：最小费
 * 算法：将输入序列相邻相等的驱去重后，如每次都替换，则总花费为新序列的重量和。在序列中，两个相同的球之间的左闭右开序列区间如果放在同一框内，则总花费可减去该球重量。建图时可将上述区间的起点和终点建容量1花费负重量的边，再用容量为INF花费0的边将整个图连起来。求最小费用流即为可以节约的最大值的相反数，加上预处理的原始总重量即为答案。因为图有负环，所以求最短增广路不能用Dijkstra，改用Bellman-Ford。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;

int a[10010], w[10010];
int pre[10010];

struct Edge {
  Edge() {}

  Edge(int _v, int _cap, int _cost, int _rev) : v(_v), cap(_cap), cost(_cost), rev(_rev) {}

  int v, cap, cost, rev;
};

vector<Edge> e[10010];
int n;
int d[10010];
int pv[10010], pe[10010];

void AddEdge(int u, int v, int cap, int cost) {
  e[u].push_back(Edge(v, cap, cost, e[v].size()));
  e[v].push_back(Edge(u, 0, -cost, e[u].size() - 1));
}

int MinCostFlow(int s, int t, int f) {
  int ans = 0;
  while (f > 0) {
    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    bool update = true;
    while (update) {
      update = false;
      for (int i = 0; i < n; ++i) {
        if (d[i] == INF) continue;
        for (int j = 0; j < e[i].size(); ++j) {
          Edge &te = e[i][j];
          if (te.cap > 0 && d[te.v] > d[i] + te.cost) {
            d[te.v] = d[i] + te.cost;
            pv[te.v] = i;
            pe[te.v] = j;
            update = true;
          }
        }
      }
    }

    if (d[t] == INF) {
      return -1;
    }

    int cur = f;
    for (int i = t; i != s; i = pv[i]) {
      cur = min(cur, e[pv[i]][pe[i]].cap);
    }
    ans += cur * d[t];
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
  int M, N, K, ans = 0;
  scanf("%d%d%d", &M, &N, &K);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &w[i]);
  }
  for (int i = 0; i < K; ++i) {
    scanf("%d", &a[i]);
    --a[i];
  }
  K = unique(a, a + K) - a;

  memset(pre, -1, sizeof(pre));
  for (int i = 0; i < K; ++i) {
    ans += w[a[i]];
    if (pre[a[i]] != -1) {
      AddEdge(pre[a[i]], i - 1, 1, -w[a[i]]);
    }
    pre[a[i]] = i;
  }
  for (int i = 1; i < K; ++i) {
    AddEdge(i - 1, i, M - 1, 0);
  }
  n = K;
  ans += MinCostFlow(0, n - 1, M - 1);
  printf("%d\n", ans);

  return 0;
}
