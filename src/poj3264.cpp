/*
 * POJ 3264: Balanced Lineup
 * 题意：奶牛站成一排，给出所有牛身高。多个查询。每次询问某个区间内的身高差的最大值。
 * 类型：线段树
 * 算法：使用线段树自底向上保存每个树节点的最大值和最小值，对于每个询问自顶向下查询最大值和最小值相减。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 50010;
const int MAXM = 1 << 17;

int mi[MAXM], ma[MAXM];
int c[50010];
int n;

#define lchild rt << 1, l, (l + r) >> 1
#define rchild rt << 1 | 1, ((l + r) >> 1) + 1, r

void update(int rt, int l, int r) {
  if (l == r) {
    mi[rt] = ma[rt] = c[l];
    return;
  }
  update(lchild);
  update(rchild);
  mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
  ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);
}

void query(int rt, int l, int r, int ql, int qr, int &mic, int &mac) {
  if (ql <= l && r <= qr) {
    mic = min(mic, mi[rt]);
    mac = max(mac, ma[rt]);
    return;
  }

  int m = (l + r) >> 1;
  if (ql <= m) {
    query(lchild, ql, qr, mic, mac);
  }
  if (qr > m) {
    query(rchild, ql, qr, mic, mac);
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
  update(1, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    int mic, mac;
    mic = ma[1];
    mac = mi[1];
    query(1, 0, n - 1, a - 1, b - 1, mic, mac);
    printf("%d\n", mac - mic);
  }
  return 0;
}
