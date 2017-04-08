/*
 * POJ 2975: Nim
 * 题意：给出每堆石头的数量，问转移到必败态的方法有多少种。
 * 类型：Nim博弈
 * 算法：若某堆石头数量大于其他所有的xor，则可将其变为其他值的xor，使得全部的xor为0。
 */


#include <cstdio>

int a[1010];

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    int s = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      s ^= a[i];
    }
    int ans = 0;
    for (int i = 0 ;i < n; ++i) {
      if ((s ^ a[i]) < a[i]) ++ans;
    }
    printf("%d\n", ans);
  }
  return 0;
}