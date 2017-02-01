/*
 * POJ 1222: EXTENDED LIGHTS OUT
 * 题意：5x6的01矩阵，反转一个数会将上下左右也同时反转。求
 * 类型：位运算+贪心（／高斯消元）
 * 算法：枚举首列反转动作的二进制表示，当某行及之前的反转动作确定后，当前灯的状态只能由下一列对应行的动作改变，故可推导出之后所有列的动作。
 */

#include <cstdio>

int a[6][7], b[7][8];

int main() {
  int T, tc = 0;
  scanf("%d", &T);
  while (T--) {
    for (int i = 1; i <= 5; ++i)
      for (int j = 1; j <= 6; ++j)
        scanf("%d", &a[i][j]);
    for (int k = (1 << 5) - 1; k >= 0; --k) {
      int t = k;
      for (int i = 1; i <= 5; ++i) {
        b[i][1] = t & 1;
        t >>= 1;
      }
      for (int j = 2; j <= 7; ++j)
        for (int i = 1; i <= 5; ++i)
          b[i][j] = a[i][j - 1] ^ b[i][j - 1] ^ b[i - 1][j - 1] ^ b[i + 1][j - 1] ^ b[i][j - 2];

      bool ok = true;
      for (int i = 1; i <= 5; ++i) {
        if (b[i][7]) {
          ok = false;
          break;
        }
      }
      if (ok) break;
    }

    printf("PUZZLE #%d\n", ++tc);
    for (int i = 1; i <= 5; ++i) {
      for (int j = 1; j < 6; ++j) {
        printf("%d ", b[i][j]);
      }
      printf("%d\n", b[i][6]);
    }
  }
  return 0;
}

