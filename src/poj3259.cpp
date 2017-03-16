/*
 * POJ 3259: Wormholes
 * 题意：多个点之间存在双向的正权边和单向的负权边，问是否存在负圈。
 * 类型：最短路+负圈
 * 算法：Bellman-Ford，第|V|次迭代依然可以更新最短路数组，则存在未收敛的点，即存在负圈。
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

struct E{
  int u, v, c;
}e[5210];

int ne;
int nv;

int d[510];

bool BellmanFord() {
  for(int i = 1; i < nv; ++i) {
    for(int j = 0; j < ne; ++j) {
      int u = e[j].u;
      int v = e[j].v;
      int c = e[j].c;
      d[v] = min(d[v], d[u] + c);
    }
  }
  for(int j = 0; j < ne; ++j) {
    int u = e[j].u;
    int v = e[j].v;
    int c = e[j].c;
    if(d[v] > d[u] + c) {
      return false;
    }
  }
  return true;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int T, m, w;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d%d", &nv, &m, &w);
    ne = m * 2 + w;
    memset(d, 0x3f, sizeof(d));
    d[0] = 0;
    ne = 0;
    int u, v, c;
    while(m--) {
      scanf("%d%d%d", &u, &v, &c);
      e[ne].u = u;
      e[ne].v = v;
      e[ne].c = c;
      ++ne;
      e[ne].v = u;
      e[ne].u = v;
      e[ne].c = c;
      ++ne;
    }
    while(w--) {
      scanf("%d%d%d", &u, &v, &c);
      e[ne].u = u;
      e[ne].v = v;
      e[ne].c = -c;
      ++ne;
    }
    bool sp = BellmanFord();
    printf("%s\n", sp?"NO":"YES");
  }
  return 0;
}