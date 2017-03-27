/*
 * POJ 3254: Corn Fields
 * 题意：m行n列的01矩阵内，挑选若干不相邻且为1的格子。求有多少种选法。
 * 类型：状态DP
 * 算法：二进制表示某行被选的状态，它由与它异或后的状态的无相邻1的子集转移来。利用滚动数组节约内存。
 */


#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = 100000000;

int d[2][1 << 12];
int cur;
int mat[13];
int s1[1 << 12], s2[1 << 12];
int c1, c2;
int m, n;

int ADD(int a, int b) {
  return (a + b) % MOD;
}

void gao(int a, int *s, int &c) {
  int b[12];
  int c1 = 0;
  while (a) {
    b[c1++] = a & -a;
    a -= a & -a;
  }
  c = 0;
  for (int i = (1 << c1) - 1; i >= 0; --i) {
    int t = 0, ti = i;
    for (int j = 0; j < c1 && ti; ++j) {
      if (ti & 1) {
        t |= b[j];
      }
      ti >>= 1;
    }
    int tt = t;
    while (tt) {
      if ((tt & 1) && (tt >> 1 & 1)) break;
      tt >>= 1;
    }
    if (tt == 0) s[c++] = t;
  }
}

int main() {
  int t, x, y;
  scanf("%d%d", &m, &n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &t);
      mat[i] <<= 1;
      mat[i] |= t;
    }
  }
  mat[m++] = 0;
  cur = 0;
  d[cur][0] = 1;
  for (int i = 0; i < m; ++i) {
    gao(mat[i], s1, c1);
    for (int j = 0; j < c1; ++j) {
      x = s1[j];
      gao(((1 << n) - 1) ^ x, s2, c2);
      for (int k = 0; k < c2; ++k) {
        y = s2[k];
        d[1 - cur][x] = ADD(d[1 - cur][x], d[cur][y]);
      }
    }
    cur = 1 - cur;
    memset(d[1 - cur], 0, sizeof(d[0]));
  }
  printf("%d\n", d[cur][0]);

  return 0;
}
