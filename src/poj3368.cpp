/*
 * POJ 3368: Frequent values
 * 题意：奶牛站成一排，给出所有牛身高。多个查询。每次询问某个区间内的身高差的最大值。
 * 类型：线段树
 * 算法：使用线段树自底向上保存每个树节点的最大值和最小值，对于每个询问自顶向下查询最大值和最小值相减。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100010;
const int MAXM = 1 << 18;

#define lchild (rt << 1)
#define rchild (rt << 1 | 1)

int lc[MAXM], rc[MAXM], sc[MAXM];
int a[MAXN];

void update(int rt, int l, int r) {
  if (l == r) {
    sc[rt] = lc[rt] = rc[rt] = 1;
    return;
  }
  int m = (l + r) >> 1;
  update(lchild, l, m);
  update(rchild, m + 1, r);
  sc[rt] = max(sc[lchild], sc[rchild]);
  lc[rt] = lc[lchild];
  rc[rt] = rc[rchild];
  if (a[m] == a[m + 1]) {
    sc[rt] = max(sc[rt], rc[lchild] + lc[rchild]);
    if (lc[lchild] == m - l + 1) {
      lc[rt] = lc[lchild] + lc[rchild];
    }
    if (rc[rchild] == r - m) {
      rc[rt] = rc[lchild] + rc[rchild];
    }
  }
}

void query(int rt, int l, int r, int ql, int qr, int &ans, int &left, int &right) {
  if (ql <= l && r <= qr) {
    ans = max(ans, sc[rt]);
    left = lc[rt];
    right = rc[rt];
    return;
  }
  int m = (l + r) >> 1;
  int lleft, lright, rleft, rright;
  lleft = lright = rleft = rright = 0;
  if (ql <= m) {
    query(lchild, l, m, ql, qr, ans, lleft, lright);
  }
  if (qr > m) {
    query(rchild, m + 1, r, ql, qr, ans, rleft, rright);
  }
  left = lleft;
  right = rright;
  if (ql <= m && qr > m && a[m] == a[m + 1]) {
    ans = max(ans, lright + rleft);
    if (left == m - l + 1) {
      left += rleft;
    }
    if (right == r - m) {
      right += lright;
    }
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n, q;
  while (scanf("%d", &n) != EOF && n) {
    scanf("%d", &q);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    update(1, 0, n - 1);
    for (int i = 0; i < q; ++i) {
      int ql, qr;
      scanf("%d%d", &ql, &qr);
      int ans, left, right;
      ans = left = right = 0;
      query(1, 0, n - 1, ql - 1, qr - 1, ans, left, right);
      printf("%d\n", ans);
    }
  }
  return 0;
}

