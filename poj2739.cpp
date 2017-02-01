/*
 * POJ 2739: Sum of Consecutive Prime Numbers
 * 题意：将一个数分解为素数表中连续的素数的和，求分解方式有多少种。
 * 类型：尺取法
 * 算法：筛法打素数表，尺取法控制左右端点向后移动，若当前和等于待分解数则答案递增，小于则右端点右移并增加对应位置素数，否则左端点右移减小素数。
 */

#include <cstdio>

int p[10010 >> 3], cntp;
bool np[10010];

void SievePrime(int n) {
  int i, j, t;
  for (i = 2; i <= n; ++i) {
    if (!np[i]) {
      p[cntp++] = i;
    }
    for (j = 0; j < cntp && (t = i * p[j]) <= n; ++j) {
      np[t] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

int main() {
  SievePrime(10000);
  int n;
  while (scanf("%d", &n) != EOF && n) {
    int i = 0, j = 1, ans = 0;
    int tmp = p[0];
    while (i < j && j <= cntp) {
      if (tmp == n) {
        ++ans;
        tmp -= p[i++];
        tmp += p[j++];
      } else if (tmp < n) {
        tmp += p[j++];
      } else {
        tmp -= p[i++];
        if (i == j) tmp += p[j++];
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}