/*
 * POJ 3293: Rectilinear polygon
 * 题意：给出平面若干点，问是否可以构成直线型多边形。直线型多边形要求至少4个顶点，每条边都是横线或竖线，边不相交，每个顶点恰好是一条横线和一条竖线的端点。
 * 类型：扫描线+树状数组+并查集
 * 算法：将x坐标离散化，点按先y后x升序排列。扫描线沿着y线向上。相邻两个点y必须相同，将其连接并加入并查集。用数组标记每个离散化后的x处向上的竖线起点，并加入树状数组。用线段和判断某横线是否被从下面上来的竖线穿越。最后用并查集检查整个图是否联通。
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100010;

struct P {
  P() {}

  P(int _x, int _y) : x(_x), y(_y) {}

  int x, y;

  bool operator<(const P &p) const {
    if (y != p.y) return y < p.y;
    return x < p.x;
  }

  bool operator==(const P &p) const {
    return x == p.x && y == p.y;
  }
} p[MAXN];

int x[MAXN], y[MAXN];
int nx, ny;

int bit[MAXN];

void Update(int i, int c, int n) {
  while (i <= n) {
    bit[i] += c;
    i += i & -i;
  }
}

int Query(int i, int n) {
  int ret = 0;
  while (i > 0) {
    ret += bit[i];
    i -= i & -i;
  }
  return ret;
}

int Query(int a, int b, int n) {
  return Query(b, n) - Query(a - 1, n);
}

int fa[MAXN];

int FindFa(int x) {
  if (fa[x] != x) fa[x] = FindFa(fa[x]);
  return fa[x];
}

void Merge(int a, int b) {
  a = FindFa(a);
  b = FindFa(b);
  fa[a] = b;
}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int T, n;
  scanf("%d", &T);
  while (T--) {
    int ans = 0;
    int h;
    memset(bit, 0, sizeof(bit));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", &x[i], &y[i]);
      p[i] = P(x[i], y[i]);
    }

    if (n & 1) {
      printf("-1\n");
      goto L;
    }

    sort(x + 1, x + 1 + n);
    nx = unique(x + 1, x + 1 + n) - x - 1;
    sort(y + 1, y + 1 + n);
    ny = unique(y + 1, y + 1 + n) - y - 1;
    for (int i = 1; i <= n; ++i) {
      p[i].x = lower_bound(x + 1, x + 1 + nx, p[i].x) - x;
      p[i].y = lower_bound(y + 1, y + 1 + ny, p[i].y) - y;
    }
    sort(p + 1, p + 1 + n);

    for (int i = 1; i<= n; ++i) {
      fa[i] = i;
    }

    for (int i = 1; i < n; i += 2) {
      if (p[i].y != p[i + 1].y) {
        printf("-1\n");
        goto L;
      }
      if (Query(p[i].x + 1, p[i + 1].x - 1, nx)) {
        printf("-1\n");
        goto L;
      }
      for (int j = 0; j < 2; ++j) {
        int t = Query(p[i + j].x, p[i + j].x, nx);
        if (t) {
          ans += y[p[i + j].y] - y[p[t].y];
          Merge(i + j, t);
          Update(p[i + j].x, -t, nx);
        } else {
          Update(p[i + j].x, i + j, nx);
        }
      }
      ans += x[p[i + 1].x] - x[p[i].x];
      Merge(i, i + 1);
    }
    if (Query(1, nx, nx)) {
      printf("-1\n");
      goto L;
    }

    h = FindFa(1);
    for (int i = 2; i <= n; ++i) {
      if (FindFa(i) != h) {
        printf("-1\n");
        goto L;
      }
    }
    printf("%d\n", ans);
    L:;
  }
  return 0;
}
