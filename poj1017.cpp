/*
 * POJ 1017: Packets
 * 题意：给出边长为1～6的正方形若干，求用最少的边长为6的正常形装下他们。
 * 类型：贪心
 * 算法：先放边长为6～3的，计算之前边角可以放多少边长2的，放完边长为2的，用面积计算之前空余多少边长1的，最后放1。
 */

#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int a, b, c, d, e, f;
  int t[] = {0, 5, 3, 1};
  while(scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f) != EOF) {
    if(!a && !b && !c && !d && !e && !f) break;
    int ans = f + e + d + (c + 3) / 4;
    int two = 5 * d + t[c % 4];
    if(b > two) {
      ans += (b - two + 8) / 9;
    }
    int one = ans * 36 - f * 36 - e * 25 - d * 16 - c * 9 - b * 4;
    if(a > one) {
      ans += (a - one + 35) / 36;
    }
    printf("%d\n", ans);
  }
  return 0;
}

