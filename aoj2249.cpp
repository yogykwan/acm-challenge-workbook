/*
 * AOJ 2249: Road Construction
 * 算法：给出若干双向边，每条边有长度和花费。保证从0点到其他每个点的最短路不变，删除若干边。求保留边的总花费最小值。
 * 类型：最短路
 * 算法：最短路每个点只保留一个前继，计算前继边的策略是，从该边可得到更小最短路，或相等最短路但边花费更小。
 */

#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

typedef pair<int ,int> pii;

priority_queue<pii, vector<pii>, greater<pii> > pq;

int d[10010];

struct E{
  E() {}
  E(int vv, int cc, int ww): v(vv), c(cc), w(ww) {}
  int v, c, w;
};

vector<E> e[10010];
int pre[10010];

void Dijkstra(int n, int s, int d[], vector<E> e[]) {
  memset(d + 1, 0x3f, sizeof(int) * n);
  pq.push(make_pair(d[s]=0, s));
  while(!pq.empty()) {
    int u, v, c, m;
    m = pq.top().first;
    u = pq.top().second;
    pq.pop();
    if(m > d[u]) {
      continue;
    }
    for(vector<E>::iterator it = e[u].begin(); it != e[u].end(); ++it){
      const E &edge = *it;
      v = edge.v;
      c = edge.c;
      int t = d[u] + c;
      if(t < d[v]) {
        pq.push(make_pair(d[v]=t, v));
        pre[v] = edge.w;
      } else if(t == d[v]) {
        pre[v] = min(pre[v], edge.w);
      }
    }
  }
}

int main() {
  int n, m, u, v, c, w;

  while(scanf("%d%d", &n, &m) != EOF && n) {
    for(u = 1; u <= n; ++u) {
      e[u].clear();
    }
    while (m--) {
      scanf("%d%d%d%d", &u, &v, &c, &w);
      e[u].push_back(E(v, c, w));
      e[v].push_back(E(u, c, w));
    }
    Dijkstra(n, 1, d, e);

    int ans = 0;
    for (u = 2; u <= n; ++u) {
      ans += pre[u];
    }
    printf("%d\n", ans);
  }
  return 0;
}