/*
 * POJ 1466: Girls and Boys
 * 题意：学生包括男女，某些男女间存在恋爱关系，求任意两人间无恋爱关系的最大的集合。
 * 类型：二分匹配
 * 算法：二分图中，最大匹配=最小顶点覆盖数。一般图中，最小顶点覆盖数+最大独立集=顶点总数。本题因为没有给出男女，可以让每个学生和自己的副本存在二分图左右两侧，最大匹配／2即为原二分图中的最大匹配。顶点数减去原最大匹配即为所求最大独立子集。
 */

#include <cstdio>
#include <cstring>

using namespace std;

bool e[510][510];
bool vis[510];
int rec[510];
int n1, n2;

bool Dfs(int u) {
  for (int i = 0; i < n2; ++i) {
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
  for (int i = 0; i < n1; ++i) {
    memset(vis, 0, sizeof(vis));
    if (Dfs(i)) {
      ++ans;
    }
  }
  return ans;
}

struct Slide {
  int x1, x2, y1, y2;
} slide[30];

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  while (scanf("%d", &n) != EOF && n) {
    n1 = n2 = n;
    memset(e, 0, sizeof(e));
    int i, j, t;
    for (int k = 0; k < n; ++k) {
      scanf("%d: (%d)", &i, &t);
      while (t--) {
        scanf("%d", &j);
        e[i][j] = 1;
      }
    }
    printf("%d\n", n - Hungary() / 2);
  }
  return 0;
}
