/*
 * GCJ 2009 Final B: Min Perimeter
 * 题意：给出若干平面上的点，任选三个不同点可组成三角形。求三角形的最小周长。
 * 类型：平面分治
 * 算法：每次用垂线将平面一分为二，假设此时子问题已解决并得到最小解p。考虑三个点分属左右两侧的三角形，其三点会被限制在一个以垂线为轴、高为p/2、宽为p的矩形内。枚举最低点，则另两个点也可遍历。
 */


#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;


struct Point {
  Point() {}

  Point(int xx, int yy) : x(xx), y(yy) {};
  int x, y;

  bool operator==(const Point &p) const {
    return x == p.x && y == p.y;
  }
};

bool CmpX(const Point &a, const Point &b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

bool CmpY(const Point &a, const Point &b) {
  if (a.y != b.y) return a.y < b.y;
  return a.x < b.x;
}

Point p[1000010];

int n;

double ans;

double CalD(const Point &a, const Point &b) {
  return sqrt(1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y));
}

double CalP(const Point &a, const Point &b, const Point &c) {
  double p = 0;
  p += CalD(a, b);
  p += CalD(b, c);
  p += CalD(c, a);
  return p;
}

void Gao(int l, int r, const vector<Point> &py) {
  if (r - l < 3) return;
  int m = (l + r) >> 1;
  vector<Point> pl, pr;
  pl.reserve(r - l);
  pr.reserve(r - l);
  int line = p[m].x;
  for (auto &point: py) {
    if (point.x < line) {
      pl.push_back(point);
    } else {
      pr.push_back(point);
    }
  }
  Gao(l, m, pl);
  Gao(m, r, pr);
  double left = p[m].x - ans / 2, right = p[m].x + ans / 2;

  static vector<Point> q;
  q.clear();
  q.reserve(r - l);

  for (auto &point: py) {
    if (point.x > left && point.y < right) {
      q.push_back(point);
    }
  }

  int pt1 = 0, pt2 = 1;
  int np = py.size();

  for (pt1 = 0; pt1 < np - 2; ++pt1) {
    while (pt2 < np && py[pt2].y - py[pt1].y < ans / 2) {
      ++pt2;
    }
    for (int i = pt1 + 1; i < pt2; ++i) {
      for (int j = i + 1; j < pt2; ++j) {
        ans = min(ans, CalP(py[pt1], py[i], py[j]));
      }
    }
  }
}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
//  freopen("/Users/yogy/Downloads/gcj.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int tc = 1; tc <= T; ++tc) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &p[i].x, &p[i].y);
    }
    sort(p, p + n, CmpX);
    n = (int) (unique(p, p + n) - p);
    ans = 1.0e12;
    vector<Point> py(p, p + n);
    sort(py.begin(), py.end(), CmpY);
    Gao(0, n, py);
    printf("Case #%d: %.15e\n", tc, ans);
  }
  return 0;
}
