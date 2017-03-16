/*
 * POJ 1201: Intervals
 * 题意：给出n个区间，每个区间对应一个个数阈值ci。构造集合，使得它与每个区间的交集不小于ci个。求集合的最小有多少个元素。
 * 类型：贪心+线段树+二分（／差分约束）
 * 算法：区间按右端点排序。利用线段树懒惰标记，将段内已选数的个数更新或求和。根据贪心每次应从右端点向左添加一段前缀。遍历区间时，二分线段树求到的和以得到左端点，再将后缀放入线段树更新。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 50010;
const int MAXM = 1 << 17;

#define lchild rt << 1, l, m, ql, qr
#define rchild rt << 1 | 1, m + 1, r, ql, qr

int sum[MAXM], lazy[MAXM];

void down(int rt, int l, int r, int m) {
  if (lazy[rt]) {
    lazy[rt << 1] = 1;
    lazy[rt << 1 | 1] = 1;
    sum[rt << 1] = m - l + 1;
    sum[rt << 1 | 1] = r - m;
    lazy[rt] = 0;
  }
}

void up(int rt) {
  sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int rt, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) {
    lazy[rt] = 1;
    sum[rt] = r - l + 1;
    return;
  }
  int m = (l + r) >> 1;
  down(rt, l, r, m);
  if (ql <= m) {
    update(lchild);
  }
  if (qr > m) {
    update(rchild);
  }
  up(rt);
}

int query(int rt, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[rt];
  }
  int ans = 0;
  int m = (l + r) >> 1;
  down(rt, l, r, m);
  if (ql <= m) {
    ans += query(lchild);
  }
  if (qr > m) {
    ans += query(rchild);
  }
  return ans;
}

struct Seg {
  int a, b, c;

  bool operator<(const Seg &s) const {
    return b < s.b;
  }
} seg[MAXN];

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &seg[i].a, &seg[i].b, &seg[i].c);
  }
  sort(seg, seg + n);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int &a = seg[i].a;
    int &b = seg[i].b;
    int &c = seg[i].c;
    int need = c - query(1, 0, 50000, a, b);
    if (need > 0) {
      ans += need;
      int l, r, m, t;
      l = a;
      r = b + 1;
      while (l + 1 < r) {
        m = (l + r) >> 1;
        t = b - m + 1 - query(1, 0, 50000, m, b);
        if (t >= need) {
          l = m;
        } else {
          r = m;
        }
      }
      update(1, 0, 50000, l, b);
    }
  }
  printf("%d\n", ans);
  return 0;
}

