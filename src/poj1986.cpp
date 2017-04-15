/*
 * POJ 1986: Distance Queries
 * 题意：给出一棵树和每边权重，求询问的某两点的距离。
 * 类型：LCA
 * 算法：得到每个结点离虚拟根0的深度和距离，倍增法得到每个结点深度差为2次幂的上游结点。询问时，通过二分找到最近公共祖先，两点距离为各自离根的距离相加再减去2倍lca离根的距离。
 */


#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;


typedef pair<int, int> pii;

vector<pii> e[40010];

int dep[40010];
int ans[40010][17];
int path[40010];

void InitLsa(int u, int p, int step, int len = 0) {
  path[u] = len;
  dep[u] = step;
  ans[u][0] = p;
  for (int k = 1; k < 17 && ans[u][k - 1]; ++k) {
    ans[u][k] = ans[ans[u][k - 1]][k - 1];
  }
  for (vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = it->first;
    if (v == p) continue;
    InitLsa(v, u, step + 1, len + it->second);
  }
}

int GetLsa(int u, int v) {
  if (dep[u] > dep[v]) {
    int t = u;
    u = v;
    v = t;
  }
  for (int k = 0; k < 17 && dep[v] != dep[u]; ++k) {
    if (((dep[v] - dep[u]) >> k) & 1) {
      v = ans[v][k];
    }
  }
  if (u == v) return u;

  for (int k = 16; k >= 0; --k) {
    if (ans[u][k] != ans[v][k]) {
      u = ans[u][k];
      v = ans[v][k];
    }
  }
  return ans[u][0];
}

int GetDist(int u, int v) {
  int lca = GetLsa(u, v);
  return path[u] + path[v] - 2 * path[lca];
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n, m;
  scanf("%d%d", &n, &m);

  while (m--) {
    int u, v, c;
    char op[5];
    scanf("%d%d%d%s", &u, &v, &c, op);
    e[u].push_back(make_pair(v, c));
    e[v].push_back(make_pair(u, c));
  }

  InitLsa(1, 0, 1);

  int qq;
  scanf("%d", &qq);
  while (qq--) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", GetDist(u, v));
  }
  return 0;
}
