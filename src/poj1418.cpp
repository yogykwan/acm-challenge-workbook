/*
 * POJ 1418: Viva Confetti
 * 题意：在平面上顺序放置多个圆，给出圆心位置和大小。某圆被其上的若干圆完全覆盖则不可见，求最终肉眼可见的圆的数量。
 * 类型：计算几何
 * 算法：若圆与其他圆相交且某部分可见，则可见部分必为相交弧围成的部分。枚举某圆，求出其他圆与它的交点后，可将该圆的弧分段。对于每段取中点向内外各移动一小段距离，覆盖这些点的最顶层圆必为可见圆。
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-14;

double sd[] = {-EPS, EPS};
double x[110], y[110], r[110];

bool up[110];

double a[210];

double GaoDistance(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    memset(up, 0, sizeof(up));
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int cnt = 0;
      for (int j = i + 1; j < n; ++j) {
        double d = GaoDistance(x[i], y[i], x[j], y[j]);
        if (d >= r[i] + r[j]) continue;
        if (r[i] > r[j] && d <= r[i] - r[j]) continue;
        if (r[j] > r[i] && d <= r[j] - r[i]) {
          goto L;
        }
        double slope = atan2(y[j] - y[i], x[j] - x[i]);
        double rotate = acos((r[i] * r[i] + d * d - r[j] * r[j]) / 2.0 / d / r[i]);
        double start = slope - rotate;
        double end = slope + rotate;
        a[cnt++] = start < -PI ? start + 2 * PI : start;
        a[cnt++] = end > PI ? end - 2 * PI : end;
      }

      if (cnt == 0) {
        up[i] = 1;
      } else {
        a[cnt++] = -PI;
        a[cnt++] = PI;
        sort(a, a + cnt);
        for (int j = 1; j < cnt; ++j) {
          double angle = (a[j - 1] + a[j]) / 2;
          double xx, yy;
          xx = x[i] + cos(angle) * r[i];
          yy = y[i] + sin(angle) * r[i];
          for (int t = 0; t < 2; ++t) {
            double tx, ty;
            tx = xx + cos(angle) * sd[t];
            ty = yy + sin(angle) * sd[t];
            for (int k = n - 1; k >= 0; --k) {
              if (GaoDistance(tx, ty, x[k], y[k]) <= r[k]) {
                up[k] = 1;
                break;
              }
            }
          }
        }
      }
      L:;
    }
    for (int i = 0; i < n; ++i) {
      ans += up[i];
    }
    printf("%d\n", ans);
  }
  return 0;
}

