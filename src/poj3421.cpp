/*
 * POJ 3421: X-factor Chains
 * 题意：一条整数链，要求相邻两数前一个整除后一个。给出链尾的数，求链的最大长度以及满足最大长度的不同链的数量。
 * 类型：因式分解+排列组合
 * 算法：因式分解的素因子个数即为链长，链中后一个数等于前一个数乘以某素因子，所以链的数量即为这些因子不全相异的全排列数：A!/(a1!a2!a3!..)
 */

#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long LL;

int p[22], a[22];
int cnt;

int main() {
  int n, i, j;
  while(scanf("%d", &n) != EOF) {
    cnt = 0;
    for(i = 2; i <= sqrt(n); ++i) {
      if(n % i == 0) {
        p[cnt] = i;
        n /= i;
        a[cnt++] = 1;
      }
      while(n % i == 0) {
        a[cnt-1]++;
        n /= i;
      }
    }
    if(n > 1) {
      p[cnt] = n;
      a[cnt++] = 1;
    }
    LL ans = 1;
    int A = 0;
    for(i = 0; i < cnt; ++i) {
      A += a[i];
    }
    for(i = a[0] + 1; i <= A; ++i) {
      ans *= i;
    }
    for(i = 1; i < cnt; ++i) {
      for(j = 2; j <= a[i]; ++j) {
        ans /= j;
      }
    }
    printf("%d %lld\n", A, ans);
  }
  return 0;
}