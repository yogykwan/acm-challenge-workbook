/*
 * POJ 2914: Minimum Cut
 * 题意：给出无向图及各边边权，求全局最小割。
 * 类型：图论
 * 算法：Stoer-Wangner最小割算法：初始点集V，选取任意点移到A。之后每次从V中找到A的割最大的点放入A，V中只剩1个点的时候，用它的割更新解，并将它合并到上一个加入A的节点上。如此反复，知道图中合并为1个点。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int e[510][510];
int w[510];
int id[510];
bool vis[510];

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF) {
    memset(e, 0, sizeof(e));
    for (int i = 0; i < n; ++i) id[i] = i;
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      e[u][v] += c;
      e[v][u] += c;
    }

    int ans = 0x3f3f3f3f;
    while (n > 1) {
      memset(vis, 0, sizeof(vis));
      memset(w, 0, sizeof(w));
      int s, t = 0;
      vis[0] = 1;
      for (int i = 1; i < n; ++i) {
        s = t;
        t = -1;
        for (int j = 1; j < n; ++j) {
          if (!vis[j]) {
            w[j] += e[id[j]][id[s]];
            if (t == -1 || w[j] > w[t]) {
              t = j;
            }
          }
        }
        vis[t] = 1;
      }
      ans = min(ans, w[t]);
      for (int i = 0; i < n; ++i) {
        if (i == s || i == t) continue;
        e[id[i]][id[s]] += e[id[i]][id[t]];
        e[id[s]][id[i]] += e[id[i]][id[t]];
      }
      id[t] = id[--n];
    }
    printf("%d\n", ans);
  }
  return 0;
}
