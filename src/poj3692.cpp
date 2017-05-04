/*
 * POJ 3692: Kindergarten
 * 题意：女孩间互相都认识，男孩间互相也都认识，某些男孩和女孩认识。求成员互相间都认识的最大子集。
 * 类型：二分匹配
 * 算法：构造题中关系图的补图，则补图中的最大独立集即为所求。二分图中，最大匹配=最小顶点覆盖数。一般图中，最小顶点覆盖数+最大独立集=顶点总数。
 */

#include <cstdio>
#include <cstring>

using namespace std;

bool e[210][210];
bool vis[210];
int rec[210];
int n1, n2;

bool Dfs(int u) {
  for (int i = 1; i <= n2; ++i) {
    if (e[u][i] && !vis[i]) {
      vis[i] = 1;
      if (rec[i] == -1 || Dfs(rec[i])) {
        rec[i] = u;
        return true;
      }
    }
  }
  return false;
}

int Hungary() {
  memset(rec, -1, sizeof(rec));
  int ans = 0;
  for (int i = 1; i <= n1; ++i) {
    memset(vis, 0, sizeof(vis));
    if (Dfs(i)) ++ans;
  }
  return ans;
}

int main() {
  int m, tc = 0;
  while (scanf("%d%d%d", &n1, &n2, &m) != EOF && n1 + n2 + m > 0) {
    for (int i = 1; i <= n1; ++i) {
      for (int j = 1; j <= n2; ++j) {
        e[i][j] = 1;
      }
    }
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      e[u][v] = 0;
    }
    printf("Case %d: %d\n", ++tc, n1 + n2 - Hungary());
  }
  return 0;
}