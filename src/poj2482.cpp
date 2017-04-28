/*
 * POJ 2482: Stars in Your Window
 * 题意：平面中给出若干亮度不同的星星，求用一个特定大小的矩形最多能框住的星星亮度和的最大值。
 * 类型：扫描线+线段树
 * 算法：以每个星星为中心，得到可以罩住它的矩形的左下角的范围，这些范围内的点增加星星亮度，由于落在框上的点不算，框不一定要整数起点，可另左下落在框上算。求亮度和最大的点即可。离散化x坐标，将矩形的横线段按y升序排列。一根横线从下向上扫描，遇到矩形下边将对应x范围都加亮度，上边框减亮度。每次用线段树更新和求最大值。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 10010;

struct Seg {
  Seg() {}

  Seg(LL _x1, LL _x2, LL _y, LL _t) : x1(_x1), x2(_x2), y(_y), t(_t) {}

  LL x1, x2, y, t;

  bool operator<(const Seg &s) const {
    return y < s.y;
  }
} s[MAXN << 1];

LL x[MAXN << 1];
int nx, n;
LL H, W;

LL t[1 << 16], lz[1 << 16];

void Down(int rt) {
  if (lz[rt]) {
    lz[rt << 1] += lz[rt];
    lz[rt << 1 | 1] += lz[rt];
    t[rt << 1] += lz[rt];
    t[rt << 1 | 1] += lz[rt];
    lz[rt] = 0;
  }
}

void Update(int rt, int l, int r, int a, int b, int c) {
  if (a <= l && r <= b) {
    lz[rt] += c;
    t[rt] += c;
    return;
  }
  int m = (l + r) >> 1;
  Down(rt);
  if (a <= m) {
    Update(rt << 1, l, m, a, b, c);
  }
  if (b > m) {
    Update(rt << 1 | 1, m + 1, r, a, b, c);
  }
  t[rt] = max(t[rt << 1], t[rt << 1 | 1]);
}

int main() {
  while (scanf("%d%lld%lld", &n, &W, &H) != EOF && n) {
    for (int i = 0; i < n; ++i) {
      LL a, b, c;
      scanf("%lld%lld%lld", &a, &b, &c);
      s[i] = Seg(a - W + 1, a, b - H + 1, c);
      s[i + n] = Seg(a - W + 1, a, b + 1, -c);
      x[i] = a - W + 1;
      x[i + n] = a;
    }
    sort(x, x + n * 2);
    nx = unique(x, x + n * 2) - x;

    for (int i = 0; i < n; ++i) {
      s[i].x1 = s[i + n].x1 = lower_bound(x, x + nx, s[i].x1) - x;
      s[i].x2 = s[i + n].x2 = lower_bound(x, x + nx, s[i].x2) - x;
    }
    sort(s, s + n * 2);

    LL ans = 0;
    memset(t, 0, sizeof(t));
    memset(lz, 0, sizeof(lz));
    LL line = -10000000;
    for (int i = 0; i < n << 1; ++i) {
      if (s[i].y != line) {
        ans = max(ans, t[1]);
        line = s[i].y;
      }
      Update(1, 0, nx - 1, s[i].x1, s[i].x2, s[i].t);
    }
    ans = max(ans, t[1]);
    printf("%lld\n", ans);
  }
  return 0;
}
