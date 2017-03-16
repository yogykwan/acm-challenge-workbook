/*
 * POJ 2549: Sumsets
 * 题意：给出有正有负的序列，选取4个数，使a+b+c=d。求d可能的最大值。
 * 类型：双向搜索
 * 算法：序列预处理排序；一层循环从大到小枚举d，二层枚举c；a、b初始化指向首和尾，若a+b+c-d=0则找到d，大于0则尾退，小于0则首进。O(n^3)，数据弱，AC。
 */

#include <cstdio>
#include <algorithm>

using namespace std;

int x[1010];

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
    if (n < 4) {
      printf("no solution\n");
      continue;
    }
    sort(x, x + n);
    int a, b, c, d, s, t;
    bool ok = false;
    for (d = n - 1; d >= 0; --d) {
      for (c = 0; c < n; ++c) {
        if (c == d) continue;
        a = 0;
        b = n - 1;
        t = x[c] - x[d];
        while (a < b) {
          if (a == c || a == d) ++a;
          if (b == c || b == d) --b;
          if (a >= b) break;
          s = t + x[a] + x[b];
          if (s == 0) {
            ok = true;
            break;
          } else if (s > 0) {
            --b;
          } else if (s < 0) {
            ++a;
          }
        }
        if(ok) break;
      }
      if(ok) break;
    }
    if (ok) {
      printf("%d\n", x[d]);
    } else {
      printf("no solution\n");
    }
  }
  return 0;
}