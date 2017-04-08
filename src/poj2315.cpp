/*
 * POJ 2315: Football Game
 * 题意：n个球距离门框距离不同，每次选不超过m踢，踢出距离是周长的整数倍，单次最长不超过l。问先手必胜还是后手胜。
 * 类型：Nim博弈
 * 算法：将距离除以周长变为整数，则问题转化为Nim加强。n堆石头，每次最多取m堆，每堆最多取k个。首先每堆石头对k+1取模，接下来的每堆石头转为2进制数并进行模为m+1的xor（只加不进位），结果非0则必胜，否则必败。
 */

#include <cstdio>
#include <cmath>
#include <cstring>

const double PI = acos(-1.0);

int sg[28];

int main() {
  int n, m, l, r;
  int a;
  while (scanf("%d%d%d%d", &n, &m, &l, &r) != EOF) {
    l = (int)(l / (2 * PI * r));
    memset(sg, 0, sizeof(sg));
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a);
      a = (int)(a / (2 * PI * r) + 1) % (l + 1);
      int j = 0;
      while (a) {
        sg[j++] += a & 1;
        a >>= 1;
      }
    }
    bool ok = false;
    for (int j = 0; j < 28; ++j) {
      if (sg[j] % (m + 1)) {
        ok = true;
        break;
      }
    }
    printf("%s\n", ok ? "Alice" : "Bob");
  }
  return 0;
}
