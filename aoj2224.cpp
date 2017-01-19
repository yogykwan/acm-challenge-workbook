/*
 * AOJ 2224: Save Your Cats
 * 题意：给出一个图，去除每条边的花费为边的长度，求用最少的花费去除部分边使得图中无圈。
 * 类型：最小生成树
 * 算法：要求去除的边总长最短，则留下的森林的边长和应最大。最大生成森林问题可将Kruskal算法变形为每次取最大边，再用并查集判断连节。
 */

#include <cstdio>
#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

struct E{
  E() {}
  E(int uu, int vv, double cc): u(uu), v(vv), c(cc) {}
  bool operator > (const E& e) const {
    return c < e.c;
  }
  int u, v;
  double c;
};

int fa[10010];
priority_queue<E, vector<E>, greater<E> > pq;

int find(int x) {
  if(x == fa[x]) return x;
  return fa[x] = find(fa[x]);
}

double Kruskal(int n) {
  for(int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  int cnt = 1;
  double ans = 0;

  while(cnt < n && !pq.empty()) {
    const E& e = pq.top();
    int u, v;
    double c;
    u = e.u;
    v = e.v;
    c = e.c;
    pq.pop();

    u = find(u);
    v = find(v);
    if(u == v) continue;
    fa[u] = v;
    ans += c;
    ++cnt;
  }
  return ans;
}

double x[10010], y[10010];

int main() {
  int n, m;
  double ans = 0;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) {
    scanf("%lf%lf", &x[i], &y[i]);
  }
  while(m--) {
    int u, v;
    double c;
    scanf("%d%d", &u, &v);
    c = sqrt((x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]));
    ans += c;
    pq.push(E(u, v ,c));
  }
  ans -= Kruskal(n);
  printf("%.3f\n", ans);
  return 0;
}