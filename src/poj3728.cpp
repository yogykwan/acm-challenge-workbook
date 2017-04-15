/*
 * POJ 3728: The merchant
 * 题意：给出一棵树和每个点的价值。每次询问给出一条路径的起点终点，顺着路可以买一次卖一次，求最大利润。
 * 类型：LCA+DP
 * 算法：维护从点i向上2^k个点的最大值bg、最小值sm，最大利润up，最大亏损dw（反向即为最大盈利）。状态倍增转移，跨两段时用前半段最小值和后半段最大值。对每个询问找到lca，答案取三种情况最大值：up(left),dw(right),bg(right)-sm(left)。
 */


#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

int price[50010];
int bg[50010][17], sm[50010][17], up[50010][17], dw[50010][17];

vector<int> e[50010];

int dep[50010];
int ans[50010][17];


void InitLsa(int u, int p, int step) {
  dep[u] = step;
  ans[u][0] = p;
  bg[u][0] = price[u];
  sm[u][0] = price[u];
  up[u][0] = 0;
  dw[u][0] = 0;
  for (int k = 1; k < 17; ++k) {
    int fa = ans[u][k - 1];
    ans[u][k] = ans[fa][k - 1];
    bg[u][k] = max(bg[u][k - 1], bg[fa][k - 1]);
    sm[u][k] = min(sm[u][k - 1], sm[fa][k - 1]);
    up[u][k] = max(max(up[u][k - 1], up[fa][k - 1]), bg[fa][k - 1] - sm[u][k - 1]);
    dw[u][k] = min(min(dw[u][k - 1], dw[fa][k - 1]), sm[fa][k - 1] - bg[u][k - 1]);
  }
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (v == p) continue;
    InitLsa(v, u, step + 1);
  }
}

int GetLsa(int u, int v) {
  if (dep[u] > dep[v]) {
    int t = u;
    u = v;
    v = t;
  }
  for (int k = 0; k < 17 && dep[v] != dep[u]; ++k) {
    if ((dep[u] - dep[v]) >> k & 1) {
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

int GetMin(int u, int v) {
  int res = 0x3f3f3f3f;
  int len = dep[u] - dep[v];

  for (int k = 16; k >= 0 && len; --k) {
    if (len >> k & 1) {
      int c = ans[u][k];
      res = min(res, sm[u][k]);
      len ^= 1 << k;
      u = c;
    }
  }
  return res;
}

int GetMax(int u, int v) {
  int res = 0;
  int len = dep[u] - dep[v];
  for (int k = 16; k >= 0 && len; --k) {
    if (len >> k & 1) {
      int c = ans[u][k];
      res = max(res, bg[u][k]);
      len ^= 1 << k;
      u = c;
    }
  }
  return res;
}

int GetUp(int u, int v) {
  int res = 0;
  int len = dep[u] - dep[v];
  for (int k = 16; k >= 0 && len; --k) {
    if (len >> k & 1) {
      int c = ans[u][k];
      res = max(res, up[u][k]);
      res = max(res, GetMax(c, v) - GetMin(u, c));
      len ^= 1 << k;
      u = c;
    }
  }
  return res;
}

int GetDown(int u, int v) {
  int res = 0;
  int len = dep[u] - dep[v];
  for (int k = 16; k >= 0 && len; --k) {
    if (len >> k & 1) {
      int c = ans[u][k];
      res = min(res, dw[u][k]);
      res = min(res, GetMin(c, v) - GetMax(u, c));
      len ^= 1 << k;
      u = c;
    }
  }
  return res;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &price[i]);
  }

  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }

  memset(sm, 0x3f, sizeof(sm));

  InitLsa(1, 0, 1);

  int qq;
  scanf("%d", &qq);
  while (qq--) {
    int u, v;
    scanf("%d%d", &u, &v);
    int lca = GetLsa(u, v);
    int fa = ans[lca][0];
    int upway = GetUp(u, fa);
    int downway = -GetDown(v, fa);
    int merge = GetMax(v, fa) - GetMin(u, fa);
    int res = max(max(upway, downway), merge);
    printf("%d\n", res);
  }
  return 0;
}
