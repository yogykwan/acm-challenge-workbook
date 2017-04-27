/*
 * AOJ 2201: Immortal Jewels
 * 题意：在平面上顺序放置多个圆，给出圆心位置、半径和磁力范围。一条直线在圆的磁力范围内但不穿过圆则认为该圆被吸引。求吸引圆最多的直线的圆的数量。
 * 类型：计算几何
 * 算法：每个圆可扩展磁力范围得到磁力圆，极限情况的直线与2个圆或磁力圆相切，计算所有圆到该直线的距离是否在范围内但超过半径。PS：计算几何注意模板积累。
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <complex>
#include <vector>

using namespace std;


typedef complex<double> P;
const double PI = acos(-1.0);
const double EPS = 1e-12;

int cmp(double a, double b) {
  const double diff = a - b;
  if (fabs(diff) < EPS)
    return 0;
  else if (diff < 0)
    return -1;
  else
    return 1;
}

// 向量点乘
inline double dot(const P &a, const P &b) {
  return a.real() * b.real() + a.imag() * b.imag();
}

// 向量叉乘
inline double cross(const P &a, const P &b) {
  return a.real() * b.imag() - b.real() * a.imag();
}

struct line {
  P a, b;

  line() {}

  line(const P &p, const P &q) : a(p), b(q) {}

  // 是否平行
  inline bool parallel(const line &ln) const {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;  // 平行叉乘得到向量的模是0，也就是sin(theta)=0 <-> theta=0
  }

  // 是否相交
  inline bool intersects(const line &ln) const {
    return !parallel(ln);
  }

  // 求交点
  inline P intersection(const line &ln) const {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x * (cross(y, ln.a - a)) / cross(y, x);
  }

  // 点到直线的距离
  inline double distance(const P &p) const {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }

  // 求垂足坐标
  inline P perpendicular(const P &p) const {
    const double t = dot(p - a, a - b) / dot(b - a, b - a);
    return a + t * (a - b);
  }
};


struct circle {
  P o;
  double r;

  circle() {}

  circle(const P &p, double x) : o(p), r(x) {}

  // 通过点 p 的两条切线
  pair<P, P> tangent(const P &p) const {
    const double L = abs(o - p);
    const double M = sqrt(L * L - r * r);
    const double theta = asin(r / L);
    const P v = (o - p) / L;
    return make_pair(p + M * (v * polar(1.0, theta)), p + M * (v * polar(1.0, -theta)));
  }

  // 两个半径相等圆的两条平行外切线
  pair<line, line> outer_tangent_parallel(const circle &c) const {
    const P d = o - c.o;
    const P v = d * P(0, 1) * r / abs(d);
    return make_pair(line(o + v, c.o + v), line(o - v, c.o - v));
  }

  // 两个圆外切线
  pair<line, line> outer_tangent(const circle &c) const {
    if (cmp(r, c.r) == 0)
      return outer_tangent_parallel(c);
    if (r > c.r)
      return c.outer_tangent(*this);
    const P d = o - c.o;
    const double fact = c.r / r - 1;
    const P base = c.o + d + d / fact;
    const pair<P, P> t = tangent(base);
    return make_pair(line(base, t.first), line(base, t.second));
  }

  // 内切线
  pair<line, line> inner_tangent(const circle &c) const {
    if (r > c.r)
      return c.inner_tangent(*this);
    const P d = c.o - o;
    const double fact = c.r / r + 1;
    const P base = o + d / fact;
    const pair<P, P> t = tangent(base);
    return make_pair(line(base, t.first), line(base, t.second));
  }

  // 是否相交
  inline bool intersects(const circle &c) const {
    return !contains(c) && !c.contains(*this) && cmp(abs(o - c.o), r + c.r) <= 0;
  }

  // 是否相离
  inline bool independent(const circle &c) const {
    return cmp(abs(o - c.o), r + c.r) > 0;
  }

  // 两个圆的交点
  pair<P, P> intersection(const circle &c) const {
    const double d = abs(o - c.o);
    const double cos_ = (d * d + r * r - c.r * c.r) / (2 * d);
    const double sin_ = sqrt(r * r - cos_ * cos_);
    const P e = (c.o - o) / d;
    return make_pair(o + e * P(cos_, sin_), o + e * P(cos_, -sin_));
  }

  // 是否包含圆c
  inline bool contains(const circle &c) const {
    return cmp(abs(o - c.o) + c.r, r) < 0;
  }

  // 是否相交
  inline bool intersects(const line &ln) const {
    return cmp(abs(ln.distance(o)), r) <= 0;
  }

  // 圆心到直线的距离
  inline double distance(const line &ln) const {
    return abs(ln.distance(o));
  }

  // 圆与直线的交点
  pair<P, P> intersection(const line &ln) const {
    const P h = ln.perpendicular(o);
    const double d = abs(h - o);
    P ab = ln.b - ln.a;
    ab /= abs(ab);
    const double l = sqrt(r * r - d * d);
    return make_pair(h + l * ab, h - l * ab);
  }
};

void enum_event(const circle &c1, const circle &c2, vector<line> &lines) {
  if (c1.independent(c2))  // 两圆相离
  {
    auto outer = c1.outer_tangent(c2);
    lines.push_back(outer.first);
    lines.push_back(outer.second);
    auto inner = c1.inner_tangent(c2);
    lines.push_back(inner.first);
    lines.push_back(inner.second);
  } else if (c1.intersects(c2))  // 两圆相交或相切
  {
    auto outer = c1.outer_tangent(c2);
    lines.push_back(outer.first);
    lines.push_back(outer.second);
    auto inter = c1.intersection(c2);
    lines.push_back(line(inter.first, inter.second));  // 此时内切线不存在，使用交点形成的线代替，本题中不是极限情况
  }
}

circle cs[50][2];
vector<line> lines;

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    lines.clear();
    for (int i = 0; i < n; ++i) {
      double x, y, r, m;
      scanf("%lf%lf%lf%lf", &x, &y, &r, &m);
      cs[i][0] = circle(P(x, y), r);
      cs[i][1] = circle(P(x, y), r + m);
      for (int j = 0; j < i; ++j) {
        enum_event(cs[i][0], cs[j][0], lines);
        enum_event(cs[i][1], cs[j][0], lines);
        enum_event(cs[i][0], cs[j][1], lines);
        enum_event(cs[i][1], cs[j][1], lines);
      }
    }
    int ans = 1;
    for (auto &l: lines) {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        double d = l.distance(cs[i][0].o);
        if (cmp(d, cs[i][0].r) >= 0 && cmp(d, cs[i][1].r) <= 0) {
          ++cnt;
        }
      }
      ans = max(ans, cnt);
    }
    printf("%d\n", ans);
  }
  return 0;
}
