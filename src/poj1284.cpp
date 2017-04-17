/*
 * POJ 1284: Primitive Roots
 * 题意：给出一个素数，求它的原根个数。
 * 类型：数论
 * 算法：原根定理，如果p有原根（形如2／4／p^x/2*p^x），则它恰有φ(φ(p))个不同的原根。因为p是素数，所以p的原根个数为φ(p-1)。用筛法预处理出所有欧拉函数的值。
 */


#include <cstdio>


int p[20000];
bool np[65555];
int f[65555];
int cnt;

void Sieve(int m = 65536) {
  for (int i = 2; i <= m; ++i) {
    if (!np[i]) {
      p[cnt++] = i;
      f[i] = i - 1;
    }
    long long t;
    for (int j = 0; j < cnt && (t = 1ll * i * p[j]) <= m; ++j) {
      np[t] = 1;
      if (i % p[j] == 0) {
        f[t] = f[i] * p[j];
        break;
      } else {
        f[t] = f[i] * (p[j] - 1);
      }
    }
  }
}


int main() {
  Sieve();
  int n;
  while (scanf("%d", &n) != EOF) {
    printf("%d\n", f[n - 1]);
  }
  return 0;
}
