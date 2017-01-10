/*
 * POJ 2229: Sumsets
 * 题意：将一个数n分解为2的次幂的和，求分解方案数。
 * 类型：DP
 * 算法：若n的分解式包含1，则在n-1的分解式最后添上1，s[n]+=s[n-1]；若分解式都为偶数，则s[n]+=s[n>>1]。
 */


#include <cstdio>
#include <iostream>

using namespace std;

long long d[1000010];

int main() {
  int n;
  scanf("%d", &n);
  d[0] = 1;
  for(int i = 1; i <= n; ++i) {
    if(i & 1) {
      d[i] = d[i - 1];
    } else{
      d[i] = (d[i - 1] + d[i >> 1]) % 1000000000;
    }
  }
  printf("%lld\n", d[n]);
  return 0;
}
