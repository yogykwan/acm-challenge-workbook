/*
 * POJ 1981: Circle and Points
 * 题意：给出平面上多个点的坐标，求单位圆最多能覆盖多少个点。不存在距离为2的2点，也不存在同时处在某单位圆的3点。
 * 类型：计算几何
 * 算法：遍历点作为单位圆圆心，求其他所有点的单位圆与其相交弧。以弧上的点为圆心的答案圆可覆盖构成该段相交弧的圆的圆心。以圆心为极坐标记录交点后排序，然后逆时针单遍扫描，起点+1，终点-1，被覆盖的最多次数即为答案。
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

double x[310], y[310];

struct Node {
  double angle;
  bool start;

  bool operator<(const Node &no) const {
    if (angle != no.angle) return angle < no.angle;
    return start > no.start;
  }
} node[610];

double GaoDistance(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf", &x[i], &y[i]);
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
      int cnt = 0;
      for (int j = 0; j < n; ++j) {
        if (i == j) continue;
        double d = GaoDistance(x[i], y[i], x[j], y[j]);
        if (d > 2.0) continue;
        double slope = atan2(y[j] - y[i], x[j] - x[i]);
        double rotate = acos(d / 2.0);
        node[cnt].angle = slope - rotate;
        node[cnt++].start = 1;
        node[cnt].angle = slope + rotate;
        node[cnt++].start = 0;
      }
      sort(node, node + cnt);
      int cur = 1;
      for (int j = 0; j < cnt; ++j) {
        if (node[j].start) ++cur;
        else --cur;
        ans = max(cur, ans);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}

