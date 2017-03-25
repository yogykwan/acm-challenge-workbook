/*
 * UVa 11990: "Dynamic" Inversion
 * 题意：给出1～n的排列，每次去掉一个数，求每次去掉前的逆序。
 * 类型：平方分割
 * 算法：下标和值构成平面里的点，将平面分割为边长为n个√n的正方形。对于某个点，去掉它时影响逆序的点在左上角和右下角，可由某以原点为左下起点的矩阵相减得到。每个桶里保存横向前缀累加和，复杂度O(n√n)。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 200000;

int xy[MAXN], yx[MAXN];
LL sum[450][450];

int len, cnt;

LL query(int x, int y) {  // 原点到(x,y)矩阵内的点数
  int xx, yy;
  LL ans = 0;
  xx = x / len;
  yy = y / len;
  if (xx) {
    for (int i = 0; i < yy; ++i) {
      ans += sum[i][xx - 1];
    }
  }
  for (int i = yy * len; i <= y; ++i) {
    if (yx[i] != -1 && yx[i] <= x) ++ans;
  }
  for (int i = xx * len; i <= x; ++i) {
    if (xy[i] != -1 && xy[i] < yy * len) ++ans;
  }
  return ans;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF) {
    memset(sum, 0, sizeof(sum));
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));
    int x, y, xx, yy;
    len = int(sqrt(n));
    cnt = (n - 1) / len + 1;
    LL ans = 0;
    for (x = 0; x < n; ++x) {
      scanf("%d", &y);
      --y;
      ans += query(x, n - 1) + query(n - 1, y) - 2 * query(x, y);
      xy[x] = y;
      yx[y] = x;
      yy = y / len;
      for (xx = x / len; xx < cnt; ++xx) {
        ++sum[yy][xx];
      }
    }

    for (int i = 0; i < m; ++i) {
      scanf("%d", &y);
      printf("%lld\n", ans);
      --y;
      x = yx[y];
      xy[x] = -1;
      yx[y] = -1;
      yy = y / len;
      for (xx = x / len; xx < cnt; ++xx) {
        --sum[yy][xx];
      }
      ans -= query(x, n - 1) + query(n - 1, y) - 2 * query(x, y);
    }
  }
  return 0;
}
