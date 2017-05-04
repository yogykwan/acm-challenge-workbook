/*
 * POJ 1274: The Perfect Stall
 * 题意：每头牛有自己偏爱的牛栏列表，每个牛栏只能放一头牛。求可以被满足的牛的最大数量。
 * 类型：二分匹配
 * 算法：牛的点在左侧，牛栏的点在右侧，用偏爱关系建邻接矩阵。匈牙利算法递归求解最大二分匹配。
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
  int ans = 0;
  for (int i = 1; i <= n1; ++i) {
    memset(vis, 0, sizeof(vis));
    if (Dfs(i)) ++ans;
  }
  return ans;
}

int main() {
  while (scanf("%d%d", &n1, &n2) != EOF) {
    memset(e, 0, sizeof(e));
    memset(rec, -1, sizeof(rec));
    for (int i = 1; i <= n1; ++i) {
      int t, j;
      scanf("%d", &t);
      while (t--) {
        scanf("%d", &j);
        e[i][j] = 1;
      }
    }
    printf("%d\n", Hungary());
  }
  return 0;
}