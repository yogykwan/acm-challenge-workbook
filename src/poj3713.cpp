/*
 * POJ 3713: Transferring Sylla
 * 题意：给出一个无向图，判断是否任意两点间都存在至少3条互相独立的路，独立指公共顶点只有起点和终点。
 * 类型：图论
 * 算法：枚举每个点，删去后用Tarjan判断图中是否存在割点，如果存在则该图不满足三连通性。Tarjan中保存搜索树，多子树的根节点为割点；dfs顺序为节点编号，dp得到每个子树通过回边能回到的最小编号，若某点的子树们能回到的点大于等于自己，则该点为割点。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int del, root;
bool cut;
int dfn[510], low[510];

vector<int> e[510];
int n, m;
int tot;

void Tarjan(int u, int p) {
  if (cut) return;
  dfn[u] = low[u] = ++tot;
  int son = 0;
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (v == p || v == del) continue;
    if (!dfn[v]) {
      ++son;
      Tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if ((u == root && son > 1) || (u != root && low[v] >= dfn[u])) {
        cut = 1;
        return;
      }
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }

}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (scanf("%d%d", &n, &m) != EOF && n) {
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      e[u].push_back(v);
      e[v].push_back(u);
    }
    cut = 0;
    for (int i = 0; i < n; ++i) {
      del = i;
      memset(dfn, 0, sizeof(dfn));
      tot = 0;
      root = !i;

      Tarjan(root, -1);
      if (cut) break;
      for (int j = 0; j < n; ++j) {
        if (j != del && !dfn[j]) {
          cut = 1;
          break;
        }
      }
      if (cut) break;
    }
    printf("%s\n", cut ? "NO" : "YES");
  }
  return 0;
}
