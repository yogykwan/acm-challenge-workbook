/*
 * POJ 1258: Agri-Net
 * 题意：给出邻接矩阵，选出部分边，使得整个图连通。求边的最小总花费。
 * 类型：最小生成树
 * 算法：本题为稠密图，Prim算法求最小生成树更优，复杂度O(n^2)。（／Kruskal算法亦可）
 */

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int mat[110][110];
bool vis[110];
int d[110];

int Prim(int n) {
  int ans = 0;
  int p = 0;
  vis[0] = 1;
  for(int j = 1; j < n; ++j) {
    d[j] = mat[p][j];
  }
  for(int i = 1; i < n; ++i) {
    p = -1;
    for(int j = 1; j < n; ++j) {
      if(vis[j]) continue;
      if(p == -1 || d[j] < d[p]) {
        p = j;
      }
    }
    ans += d[p];
    vis[p] = 1;
    for(int j = 1; j < n; ++j) {
      if(vis[j]) continue;
      d[j] = min(d[j], mat[p][j]);
    }
  }
  return ans;
}

int main() {
  int n, i, j;
  while(scanf("%d", &n) != EOF) {
    memset(vis, 0, sizeof(vis));
    for(i = 0; i < n; ++i) {
      for(j = 0; j < n; ++j) {
        scanf("%d", &mat[i][j]);
      }
    }
    int ans = Prim(n);
    printf("%d\n", ans);
  }
  return 0;
}
