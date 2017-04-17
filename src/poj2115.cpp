/*
 * POJ 2115: C Looooops
 * 题意：x初值为A，迭代式为x=(x+C)%(1<<k)，问需要迭代多少次才能x=B，永远不能达到输出FOREVER。
 * 类型：数论
 * 算法：变形为Cx+(1<<k)y=B-A，扩展欧几里得求解非负的最小x，同时通过最大公约数判断是否有解。
 */


#include <cstdio>

typedef long long LL;

LL ExtGcd(LL a, LL b, LL &x, LL &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  LL g = ExtGcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

int main() {
  LL A, B, C, k, x, y, a, b, c;
  while (scanf("%lld%lld%lld%lld", &A, &B, &C, &k) != EOF && k) {
    a = C;
    b = 1ll << k;
    c = B - A;
    LL g = ExtGcd(a, b, x, y);
    if (c % g) {
      printf("FOREVER\n");
    } else {
      LL u = b / g;
      x *= c / g;
      x = (x % u + u) % u;
      printf("%lld\n", x);
    }
  }
  return 0;
}
