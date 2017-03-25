/*
 * POJ 3171: Cleaning Shifts
 * 题意：用花费不一的一些区间去覆盖某个长区间，求总花费的最小值。
 * 类型：DP+线段树
 * 算法：预处理区间按右端点升序，d[i]表示已经从头覆盖到i坐标的最小代价。遍历到区间[a,b]时，线段树求的d在[a,b]的最小值，以更新d[b]。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 10010;
const int MAXM = 1 << 18;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL mm[MAXM];
LL d[86400];

struct Cow {
  int a, b;
  LL s;

  bool operator<(const Cow &c) const {
    return b < c.b;
  }
} cows[MAXN];

void update(int rt, int l, int r, int ql, LL c) {
  mm[rt] = min(mm[rt], c);
  if (l == r) return;
  int m = (l + r) >> 1;
  if (ql <= m) {
    update(rt << 1, l, m, ql, c);
  } else {
    update(rt << 1 | 1, m + 1, r, ql, c);
  }
}

LL query(int rt, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return mm[rt];
  }
  int m = (l + r) >> 1;
  LL ans = INF;
  if (ql <= m) {
    ans = min(ans, query(rt << 1, l, m, ql, qr));
  }
  if (qr > m) {
    ans = min(ans, query(rt << 1 | 1, m + 1, r, ql, qr));
  }
  return ans;
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  int M, E;
  scanf("%d%d%d", &n, &M, &E);
  memset(mm, 0x3f, sizeof(mm));
  memset(d, 0x3f, sizeof(d));

  for (int i = 0; i < n; ++i) {
    scanf("%d%d%lld", &cows[i].a, &cows[i].b, &cows[i].s);
  }
  sort(cows, cows + n);
  for (int i = 0; i < n; ++i) {
    LL db = d[cows[i].b];
    if (cows[i].a == M) {
      d[cows[i].b] = min(db, cows[i].s);
    } else {
      d[cows[i].b] = min(db, query(1, M, E, cows[i].a - 1, cows[i].b - 1) + cows[i].s);
    }
    if (d[cows[i].b] < db) {
      update(1, M, E, cows[i].b, d[cows[i].b]);
    }
  }
  printf("%lld\n", d[E] == INF ? -1 : d[E]);
  return 0;
}
