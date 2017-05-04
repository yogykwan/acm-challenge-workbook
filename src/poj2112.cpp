/*
 * POJ 2112: Optimal Milking
 * 题意：给出多头牛和多个机器之间的直连边长，每台机器可以服务m头牛。所有牛的被满足的前提下，求牛到服务它的机器的最远距离的最小值。
 * 类型：最短路+二分+二分匹配（／最大流）
 * 算法：Floyd得到所有点之间的最短路，然后二分最远距离，不大于该距离的边可用于二分匹配。二分匹配时，将每台机器分割为m台。若此时最大匹配数为牛数则更新上届，否则下届。最终的上届即为最远距离的最小值。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

bool e[210][460];
bool vis[460];
int rec[460];
int n1, n2;
int K, C, M;
int d[240][240];

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

bool Hungary() {
  memset(rec, -1, sizeof(rec));
  for (int i = 0; i < n1; ++i) {
    memset(vis, 0, sizeof(vis));
    if (!Dfs(i)) return false;
  }
  return true;
}

void BuildGraph(int g) {
  memset(e, 0, sizeof(e));
  for (int i = 0; i < C; ++i) {
    for (int j = 0; j < K; ++j) {
      if (d[K + i][j] <= g) {
        for (int k = M * j; k < M * (j + 1); ++k) {
          e[i][k] = 1;
        }
      }
    }
  }
}

void Floyd(int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &d[i][j]);
      if (!d[i][j]) d[i][j] = INF;
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &K, &C, &M);
  n1 = C;
  n2 = K * M;
  Floyd(K + C);
  int l, r, m;
  l = 0;
  r = (K + C) * 200;
  while (l + 1 < r) {
    m = (l + r) >> 1;
    BuildGraph(m);
    (Hungary() ? r : l) = m;
  }
  printf("%d\n", r);
  return 0;
}