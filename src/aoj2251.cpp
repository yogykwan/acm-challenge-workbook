/*
 * AOJ 2251: Merry Christmas
 * 题意：给出一个带权无向图，给出多个任务，每个任务指定了在何处何时发生。求最少需要多少人才能完成所有任务。
 * 类型：最短路+二分匹配
 * 算法：先用Floyd求两两之间最短路，若两个任务时间差不超过最短路，则可以分配给同一个人。以任务和任务的副本建二分图，任务数-最大匹配／2即为所求。
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

vector<int> e[1010];
bool vis[1010];
int rec[1010];
int n1;

int n, m;
int d[110][110];

int p[1010], t[1010];

bool Dfs(int u) {
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (!vis[v]) {
      vis[v] = true;
      if (rec[v] == -1 || Dfs(rec[v])) {
        rec[v] = u;
        return true;
      }
    }
  }
  return false;
}

int Hungary() {
  int ans = 0;
  memset(rec, -1, sizeof(rec));
  for (int i = 0; i < n1; ++i) {
    memset(vis, 0, sizeof(vis));
    if (Dfs(i)) ++ans;
  }
  return ans;
}

void Floyd() {
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (scanf("%d%d%d", &n, &m, &n1) != EOF && n) {
    memset(d, 0x3f, sizeof(d));
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      d[u][v] = d[v][u] = c;
    }
    Floyd();
    for (int i = 0; i < n1; ++i) {
      scanf("%d%d", &p[i], &t[i]);
      e[i].clear();
    }
    for (int i = 0; i < n1; ++i) {
      for (int j = 0; j < n1; ++j) {
        if (i == j) continue;
        if (t[i] + d[p[i]][p[j]] <= t[j]) {
          e[i].push_back(j);
        }
      }
    }
    printf("%d\n", n1 - Hungary());
  }

  return 0;
}
