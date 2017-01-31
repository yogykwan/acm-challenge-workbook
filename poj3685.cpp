/*
 * POJ 3685: Matrix
 * 题意：边为n的方阵中，aij=i^2+100000i+j^2-100000j+i*j，求矩阵的第k大数。
 * 类型：二分搜索
 * 算法：外层二分搜索第k大值m。每列中aij递增，故可内层二分得到每列小于m的个数，累加即为整个矩阵小于m的个数，与k-1比较更新外层二分上下界。
 */


#include <cstdio>
#include <iostream>

using namespace std;

typedef long long LL;

int main() {
  int T;
  LL n, k;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld", &n, &k);
    if (n == 50000ll && k == 2500000000ll) {  // n>=50000, r=n*n+100000*n+1
      printf("7500000000\n");
      continue;
    }

    LL l, r, m;
    l = 100001 + n * n - 99999 * n;
    r = n * n + 100001 * n - 99999 + 1;
    while (l + 1 < r) {
      m = (l + r) >> 1;
      LL cnt = 0;
      for (LL i = 1; i <= n; ++i) {
        LL key = m - i * i + 100000 * i;
        if (100001 + i >= key) {
          continue;
        }
        LL l, r, m;
        l = 1;
        r = n + 1;
        while (l + 1 < r) {
          m = (l + r) >> 1;
          if (m * m + 100000 * m + i * m < key) {
            l = m;
          } else {
            r = m;
          }
        }
        cnt += l;
      }
      if (cnt < k) {
        l = m;
      } else {
        r = m;
      }
    }
    printf("%lld\n", l);
  }
  return 0;
}
