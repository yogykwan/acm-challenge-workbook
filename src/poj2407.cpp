/*
 * POJ 2407: Relatives
 * 题意：给出一个数，求比它小且与它互素的数个数。
 * 类型：数论
 * 算法：预处理筛法打素数表。分解质因数n=p1^a1*p2^a2...，则欧拉函数φ(n)=n/p1/p2/...*(p1-1)*(p2-1)*...
 */


#include <cstdio>
#include <cmath>

int prime[10010];
int cntp;
bool np[31624];

void SievePrime(int n = 31623) {
  for (int i = 2; i <= n; ++i) {
    if (!np[i]) prime[cntp++] = i;
    int t;
    for (int j = 0; j < cntp && (t = i * prime[j]) <= n; ++j) {
      np[t] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}

int main() {
  SievePrime();
  int n;
  while (scanf("%d", &n) != EOF && n) {
    int ans = n;
    int m = 0;
    int p[33];
    int a[33];
    int up = (int)sqrt(n + 1);
    for (int i = 0; i < cntp && prime[i] <= up && n > 1; ++i) {
      if (n % prime[i] == 0) {
        p[m] = prime[i];
        a[m++] = 0;
      }
      while (n % prime[i] == 0) {
        n /= prime[i];
        ++a[m - 1];
      }
    }
    if (n > 1) {
      p[m] = n;
      a[m++] = 1;
    }
    for (int i = 0; i < m; ++i) {
      ans /= p[i];
      ans *= p[i] - 1;
    }
    printf("%d\n", ans);
  }
  return 0;
}
