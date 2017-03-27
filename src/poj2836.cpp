/*
 * POJ 2836: Rectangular Covering
 * 题意：给出平面上n个点，用若干矩形将所有点覆盖，要求每个矩形覆盖至少2个点。求矩形的面积和最小值。
 * 类型：状态DP
 * 算法：状态内的点一定被覆盖，但被覆盖的点不一定在状态内，预处理出任意两点构成的矩形面积和包含的点状态。记忆化dp递归时，选取状态内的点与整个平面的点构成矩形。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int d[1 << 15];
int x[20], y[20];
int n;

int a[20][20];
int p[20][20];

void gao(int xa, int ya, int xb, int yb, int &x1, int &y1, int &x2, int &y2, int &type) {
  int t;
  if (xa > xb) {
    t = xa; xa = xb; xb = t;
  }
  if (ya > yb) {
    t = ya; ya = yb; yb = t;
  }
  x1 = xa; x2 = xb; y1 = ya; y2 = yb;
  type = 0;
  if (xa == xb) {
    ++x2;
    type = 1;
  }
  if (ya == yb) {
    ++y2;
    type = 2;
  }
}

void pre() {
  int x1, y1, x2, y2, type, t;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      gao(x[i], y[i], x[j], y[j], x1, y1, x2, y2, type);
      a[j][i] = a[i][j] = (x2 - x1) * (y2 - y1);
      t = 0;
      for (int k = 0; k < n; ++k) {
        if (x[k] >= x1 && x[k] <= x2 && y[k] >= y1 && y[k] <= y2) {
          t |= 1 << k;
        }
      }
      p[j][i] = p[i][j] = t;
    }
  }
}

int dfs(int s) {
  if (d[s] < INF) return d[s];
  int b[20], cnt = 0;
  int t = s;
  for (int i = 0; i < n; ++i) {
    if (t & 1) b[cnt++] = i;
    t >>= 1;
  }
  for (int i = 0; i < cnt; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == b[i]) continue;
      d[s] = min(d[s], dfs(s & (~p[b[i]][j])) + a[b[i]][j]);
    }
  }
  return d[s];
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (scanf("%d", &n) != EOF && n) {
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &x[i], &y[i]);
    }
    pre();
    memset(d, 0x3f, sizeof(d));
    d[0] = 0;
    printf("%d\n", dfs((1 << n) - 1));
  }
  return 0;
}

