/*
 * POJ 1286: Necklace of Beads
 * 题意：三种颜色的珠子串称一定长度的链子，翻转或旋转后重合的视为同一种，求共有多少种不同的。
 * 类型：Pólya计数
 * 算法：L=|1/G|*(m^c(p1)+m^c(p2)+...+m^c(pk))。G为置换群，m为颜色，c(pi)表示第i个置换的循环节数。同时考虑翻转和旋转，置换群大小为2n。旋转i的循环节个数为gcd(n,i)。翻转时按奇偶讨论，n为奇数时为1+(n-1)/2，共n条对称轴；偶数时对称轴分过不过珠子两种，各n/2种情况，循环节分别为(n-2)/2+2+1和n/2。
 */


#include <cstdio>

typedef long long LL;

LL Gcd(LL a, LL b) {
  for (LL t; t = b;) {
    b = a % b;
    a = t;
  }
  return a;
}

LL Pow(LL a, LL b) {
  LL ans = 1;
  while (b--) ans *= a;
  return ans;
}

int main() {
  LL n;
  while (scanf("%lld", &n) != EOF && n != -1) {
    if (n == 0) {
      printf("0\n");
      continue;
    }

    LL ans = 0;

    // rotation
    for (LL i = 0; i < n; ++i) {
      ans += Pow(3, Gcd(n, i));
    }

    // reflection
    if (n & 1) {
      ans += n * Pow(3, n / 2 + 1);
    } else {
      ans += n / 2 * (Pow(3, n / 2 + 1) + Pow(3, n / 2));
    }

    ans /= 2 * n;
    printf("%lld\n", ans);
  }
  return 0;
}
