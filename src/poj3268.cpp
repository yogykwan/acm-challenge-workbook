/*
 * POJ 3268: Silver Cow Party
 * 题意：多个点由多条单向边连通，每个点的牛要去一个特定点参加晚会然后返回自己家，求最短回路最长的牛。
 * 类型：最短路+最小堆
 * 算法：用Dijkstra计算特定点到所有点的最短路，然后将所有点反向再计算一次。两次结果相加为最短回路。
 */

#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

typedef pair<int ,int> pii;

vector<pii> ef[100010], eb[100010];
priority_queue<pii, vector<pii>, greater<pii> > pq;

int df[1010], db[1010];

void Dijkstra(int n, int s, int d[], vector<pii> e[]) {
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

    for(vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it){
      const pii &edge = *it;
      v = edge.first;
      c = edge.second;
      int t = d[u] + c;
      if(t < d[v]) {
        pq.push(make_pair(d[v]=t, v));
      }
    }
  }
}

int main() {
  int n, m, x;
  int u, v, c;
  scanf("%d%d%d", &n, &m, &x);
  while(m--) {
    scanf("%d%d%d", &u, &v, &c);
    ef[u].push_back(make_pair(v, c));
    eb[v].push_back(make_pair(u, c));
  }
  Dijkstra(n, x, df, ef);
  Dijkstra(n, x, db, eb);
  int ans = 0;
  for(u = 1; u <= n; ++u) {
    ans = max(ans, df[u] + db[u]);
  }
  printf("%d\n", ans);
  return 0;
}
